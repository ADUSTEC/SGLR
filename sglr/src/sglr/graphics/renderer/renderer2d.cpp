#include "sglr/graphics/renderer/renderer2d.h"
#include "sglr/graphics/renderer/texture.h"
#include <ext.hpp>
#include <sglr/core/log/log.h>

#define MAX_TEXTURE_SLOTS 32

namespace sglr
{
	// information needed for each vertex
	struct vdat2d
	{
		glm::vec3 position = glm::vec3(NULL);
		glm::vec4 color = glm::vec4(NULL);
		glm::vec2 uv = glm::vec2(NULL);
		// texture index
		float tInd = 0.f;
	};

	// information needed for rendering
	struct rdat2d
	{
		// lowlevel
		std::unique_ptr<vertexarray> vao;
		std::unique_ptr<vertexbuffer> vbo;
		std::unique_ptr<indexbuffer> ibo;
		
		// vertdata 
		vdat2d* vd2d = nullptr;
		vdat2d* vd2dptr = nullptr;

		// index count
		GLsizei ic = 0;

		// threshold
		static const size_t qthresh = 1000; // max amnt of quads until flush
		static const size_t vcthresh = qthresh * 4; // vertcount threshold
		static const size_t icthresh = qthresh * 6; // indexcount threshold

		// texture
		// very shortened names cause i dont want to type out the whole thing
		uint32_t txS[MAX_TEXTURE_SLOTS]; // texture slots
		uint32_t tsI = 1; // texture slot index
		uint32_t eTx = 0; // empty texture
		uint32_t eTS = 0; // empty texture slot

		int samp[MAX_TEXTURE_SLOTS]; // samplers
	};

	static rdat2d rdat;

	renderer2d::renderer2d(shader* shader) : m_shader(shader)
	{
		// extremely unlikely to happen - here just in case
		if (!m_init())
		{
			LOG_ERROR("FAILED TO INITIALIZE 2D RENDERER: {}", m_initFailReason);
			exit(-1);
		}
	}

	renderer2d::~renderer2d() 
	{ 
		rdat.vao->destroy();
		rdat.vbo->destroy();
		rdat.ibo->destroy();

		delete[] rdat.vd2d;
		delete m_shader; 
	}

    bool renderer2d::m_init() 
    {
		if (rdat.vd2d != nullptr)
		{
			m_success = 0; 
			m_initFailReason = "CALLED INIT TWICE";
		}
		else
			rdat.vd2d = new vdat2d[rdat.vcthresh];
		
		// def
		rdat.vao = std::make_unique<vertexarray>();
		rdat.vao->bind();
		
		rdat.vbo = std::make_unique<vertexbuffer>((GLsizeiptr)(rdat.vcthresh * sizeof(vdat2d)));
		
		// attribute
		rdat.vao->link(*rdat.vbo, 0, 3, GL_FLOAT, 10 * sizeof(GLfloat), 0); // position
		rdat.vao->link(*rdat.vbo, 1, 4, GL_FLOAT, 10 * sizeof(GLfloat), 3); // color
		rdat.vao->link(*rdat.vbo, 2, 2, GL_FLOAT, 10 * sizeof(GLfloat), 7); // uv
		rdat.vao->link(*rdat.vbo, 3, 1, GL_FLOAT, 10 * sizeof(GLfloat), 9); // ts

		GLuint indices[rdat.icthresh]{};
		GLuint offset = 0;

		// generate indecies
		for (int i = 0; i < rdat.icthresh; i += 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		rdat.ibo = std::make_unique<indexbuffer>(indices, sizeof(indices));

		glCreateTextures(GL_TEXTURE_2D, 1, &rdat.eTx);
		glBindTexture(GL_TEXTURE_2D, rdat.eTx);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		uint32_t hexval = 0xffffffff;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &hexval);
		rdat.txS[0] = rdat.eTx;
		for (size_t i = 1; i < MAX_TEXTURE_SLOTS; i++)
		{
			rdat.txS[i] = 0;
		}

		for (int i = 0; i < MAX_TEXTURE_SLOTS; i++)
		{
			rdat.samp[i] = i;
		}
		m_shader->enable();
		m_shader->setUniformIntV("u_tex", rdat.samp, MAX_TEXTURE_SLOTS);
		m_shader->disable();

		if (m_success == 1)
			return true;
    }

	// public
	void renderer2d::begin() 
	{
		rdat.vd2dptr = rdat.vd2d;
		m_shader->enable();
	}

	void renderer2d::drawQuadRGBA(const glm::vec3& positionxyz, const glm::vec2& sizexy, const glm::vec4& rgba)
	{
		if (rdat.ic >= rdat.icthresh)
		{
			end();
			flush();
			begin();
		}

		rdat.vd2dptr->position = positionxyz;
		rdat.vd2dptr->color = rgba;
		rdat.vd2dptr->uv = glm::vec2(0.0, 0.0);
		rdat.vd2dptr->tInd = 0.0;
		rdat.vd2dptr++;

		rdat.vd2dptr->position = { positionxyz.x + sizexy.x, positionxyz.y, positionxyz.z };
		rdat.vd2dptr->color = rgba;
		rdat.vd2dptr->uv = glm::vec2(1.0, 0.0);
		rdat.vd2dptr->tInd = 0.0;
		rdat.vd2dptr++;

		rdat.vd2dptr->position = { positionxyz.x + sizexy.x, positionxyz.y + sizexy.y, positionxyz.z };
		rdat.vd2dptr->color = rgba;
		rdat.vd2dptr->uv = glm::vec2(1.0, 1.0);
		rdat.vd2dptr->tInd = 0.0;
		rdat.vd2dptr++;

		rdat.vd2dptr->position = { positionxyz.x, positionxyz.y + sizexy.y, positionxyz.z };
		rdat.vd2dptr->color = rgba;
		rdat.vd2dptr->uv = glm::vec2(0.0, 1.0);
		rdat.vd2dptr->tInd = 0.0;
		rdat.vd2dptr++;

		rdat.ic += 6;
	}

	void renderer2d::drawQuadTEX(const glm::vec3& positionxyz, const glm::vec2& sizexy, uint32_t texture)
	{
		if (rdat.ic >= rdat.icthresh || rdat.tsI > MAX_TEXTURE_SLOTS-1)
		{
			end();
			flush();
			begin();
		}
		 
		constexpr glm::vec4 rgba = { 1.0, 1.0, 1.0, 1.0 };

		float tInd = 0.0f;
		for (uint32_t i = 1; i < rdat.tsI; i++)
		{
			if (rdat.txS[i] == texture)
			{
				tInd = (float)i;
				break;
			}
		}

		if (tInd == 0.0f)
		{
			tInd = (float)rdat.tsI;
			rdat.txS[rdat.tsI] = texture;
			rdat.tsI++;
		}

		rdat.vd2dptr->position = positionxyz;
		rdat.vd2dptr->color = rgba;
		rdat.vd2dptr->uv = glm::vec2(0.0, 0.0);
		rdat.vd2dptr->tInd = tInd;
		rdat.vd2dptr++;

		rdat.vd2dptr->position = { positionxyz.x + sizexy.x, positionxyz.y, positionxyz.z };
		rdat.vd2dptr->color = rgba;
		rdat.vd2dptr->uv = glm::vec2(1.0, 0.0);
		rdat.vd2dptr->tInd = tInd;
		rdat.vd2dptr++;

		rdat.vd2dptr->position = { positionxyz.x + sizexy.x, positionxyz.y + sizexy.y, positionxyz.z };
		rdat.vd2dptr->color = rgba;
		rdat.vd2dptr->uv = glm::vec2(1.0, 1.0);
		rdat.vd2dptr->tInd = tInd;
		rdat.vd2dptr++;

		rdat.vd2dptr->position = { positionxyz.x, positionxyz.y + sizexy.y, positionxyz.z };
		rdat.vd2dptr->color = rgba;
		rdat.vd2dptr->uv = glm::vec2(0.0, 1.0);
		rdat.vd2dptr->tInd = tInd;
		rdat.vd2dptr++;

		rdat.ic += 6;
	}

	void renderer2d::end() 
	{
		GLsizeiptr size = (uint8_t*)rdat.vd2dptr - (uint8_t*)rdat.vd2d;
		rdat.vbo->assign(rdat.vd2d, size);
	}

	void renderer2d::flush() 
	{
		for (uint32_t i = 0; i < rdat.tsI; i++)
		{
			glBindTextureUnit(i, rdat.txS[i]);
		}

		rdat.vao->bind();
		rdat.ibo->bind();
		glDrawElements(GL_TRIANGLES, rdat.ic, GL_UNSIGNED_INT, nullptr);
		rdat.ibo->unbind();
		rdat.vao->unbind();
		rdat.ic = 0;
		rdat.tsI = 1;

		m_shader->disable();
	}
	
}