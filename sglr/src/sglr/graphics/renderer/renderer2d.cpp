#include "sglr/graphics/renderer/renderer2d.h"
#include <ext.hpp>
#include <sglr/core/log/log.h>

namespace sglr
{
	// information needed for each vertex
	struct vdat2d
	{
		glm::vec3 position = glm::vec3(NULL);
		glm::vec4 color = glm::vec4(NULL);
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
		rdat.vao->link(*rdat.vbo, 0, 3, GL_FLOAT, 7 * sizeof(GLfloat), 0); // position
		rdat.vao->link(*rdat.vbo, 1, 4, GL_FLOAT, 7 * sizeof(GLfloat), 3); // color

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

		if (m_success == 1)
			return true;
    }

	// public
	void renderer2d::begin() 
	{
		rdat.vd2dptr = rdat.vd2d;
	}

	void renderer2d::draw(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		if (rdat.ic >= rdat.icthresh)
		{
			end();
			flush();
			begin();
		}

		rdat.vd2dptr->position = position;
		rdat.vd2dptr->color = color;
		rdat.vd2dptr++;

		rdat.vd2dptr->position = { position.x + size.x, position.y, position.z };
		rdat.vd2dptr->color = color;
		rdat.vd2dptr++;

		rdat.vd2dptr->position = { position.x + size.x, position.y + size.y, position.z };
		rdat.vd2dptr->color = color;
		rdat.vd2dptr++;

		rdat.vd2dptr->position = { position.x, position.y + size.y, position.z };
		rdat.vd2dptr->color = color;
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
		rdat.vao->bind();
		rdat.ibo->bind();
		glDrawElements(GL_TRIANGLES, rdat.ic, GL_UNSIGNED_INT, nullptr);
		rdat.ibo->unbind();
		rdat.vao->unbind();
		rdat.ic = 0;
	}
	
}