#include "RenderingEngine/renderengine.h"


class renderApp : public SGLR::Application
{
	private:

		// model importing will be added soon so this is a placeholder
		GLfloat vertices[8 * 8] =
		{
			// positions			// colours			// uv coords
			-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 1.0f,	0.0f, 0.0f, // purple
			-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	0.0f, 0.0f, // yellow
			 0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 1.0f,	1.0f, 0.0f, // cyan
			 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f, // white

			-0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 1.0f, // red
			-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // green
			 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // blue
			 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 1.0f  // black
		};

		GLuint indices[12 * 3]
		{
			0, 1, 2,
			0, 2, 3,
			0, 4, 7,
			0, 7, 3,
			3, 7, 6,
			3, 6, 2,
			2, 6, 5,
			2, 5, 1,
			1, 5, 4,
			1, 4, 0,
			4, 5, 6,
			4, 6, 7
		};

		std::unique_ptr<SGLR::shader> shaders;

		std::unique_ptr<SGLR::vertexarray> vao;
		std::unique_ptr<SGLR::vertexbuffer> vbo;
		std::unique_ptr<SGLR::indexbuffer> ibo;

		std::unique_ptr<SGLR::texture> texture;

		float rotation = 0;


	public:
		renderApp() {}
		~renderApp() 
		{
			vao->destroy();
			vbo->destroy();
			ibo->destroy();
			shaders->destroy();
			texture->destroy();
		}

		void onInit() override
		{
			shaders = std::make_unique<SGLR::shader>("shaders/basic_v.glsl", "shaders/basic_f.glsl");

			vao = std::make_unique<SGLR::vertexarray>();

			vao->bind();

			vbo = std::make_unique<SGLR::vertexbuffer>(vertices, sizeof(vertices));
			ibo = std::make_unique<SGLR::indexbuffer>(indices, sizeof(indices));

			ibo->bind();

			vao->link(*vbo, 0, 3, GL_FLOAT, 8, 0);
			vao->link(*vbo, 1, 3, GL_FLOAT, 8, 3);
			vao->link(*vbo, 2, 2, GL_FLOAT, 8, 6);

			vao->unbind();
			vbo->unbind();
			ibo->unbind();

			texture = std::make_unique<SGLR::texture>("textures/t_testingtexturelogostylized.png");

			shaders->enable();
			shaders->setUniformInt("tex0", 0);
			
		}

		void onRender(float deltaTime) override
		{
			
			shaders->enable();
			texture->bind();

			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 proj = glm::mat4(1.0f);

			rotation += 0.1f;

			model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
			proj = glm::perspective(glm::radians(45.0f), getViewportSize().x / getViewportSize().y, 0.01f, 100.0f);

			shaders->setUniformMat4("u_model", model);
			shaders->setUniformMat4("u_view", view);
			shaders->setUniformMat4("u_proj", proj);

			vao->bind();
			
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

			vao->unbind();

			texture->unbind();
			shaders->disable();

		}

		void onUpdate(float deltaTime) override
		{}

		void onTick(float deltaTime) override
		{}

};

int main(int argc, char** argv)
{
	SGLR::Log::Init(); // Initialize logger
	
	renderApp app;
	app.start();
	
	SGLR::Log::Shutdown(); // Destroy

	return 0;
}