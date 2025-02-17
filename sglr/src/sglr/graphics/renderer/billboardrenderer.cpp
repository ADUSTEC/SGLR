#include "sglr/graphics/renderer/billboardrenderer.h"

namespace sglr
{
	
	billboard::billboard(shader* shader, camera* camera)
		: m_shader(shader), m_camera(camera)
	{
		float bbvertices[4 * 3] =
		{
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};

		GLuint bbindices[2 * 3]
		{
			0, 3, 2,
			2, 1, 0
		};


		m_vao = new vertexarray();

		m_vao->bind();

		m_vbo = new vertexbuffer(bbvertices, sizeof(bbvertices));
		m_ibo = new indexbuffer(bbindices, sizeof(bbindices));

		m_ibo->bind();

		m_vao->link(*m_vbo, 0, 3, GL_FLOAT, 3, 0);

		m_vao->unbind();
		m_vbo->unbind();
		m_ibo->unbind();
	}

	billboard::~billboard()
	{
		delete m_shader;
		delete m_vao;
		delete m_vbo;
		delete m_ibo;
		delete m_camera;
		
	}


	void billboard::draw()
	{
		m_shader->enable();
		m_vao->bind();

		m_shader->setUniformMat4("u_projection", m_camera->getProjection());
		m_shader->setUniformMat4("u_view", m_camera->getView());

		glm::mat4 model = glm::mat4(1.0f);

		glm::vec3 cpos = m_camera->getPosition();

		glm::mat4 rotmatrix = glm::lookAt(glm::vec3(0.0f, -0.5f, 0.0f), glm::vec3(cpos.x, cpos.y, -cpos.z), m_camera->getUpVector());

		model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
		
		m_shader->setUniformMat4("u_model", model);

		m_shader->setUniformMat4("u_rot", rotmatrix); // update rotation matrix uniform

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		m_vao->unbind();
		m_shader->disable();
		
	}
}