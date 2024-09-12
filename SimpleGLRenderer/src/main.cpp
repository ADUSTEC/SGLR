#include "RenderingEngine/renderengine.h"


class renderApp : public SGLR::Application
{
	private:

		// model importing will be added soon so this is a placeholder

		GLfloat vertices[24 * 11] =
		{
			//pos                // rgb			    // uv	    // normals
			-1.0,  1.0,  1.0,	1.0f, 0.0f, 0.0f,	0.0, 1.0,	-1.0, -0.0, -0.0,
			-1.0, -1.0, -1.0,	0.0f, 1.0f, 0.0f,	1.0, 0.0,	-1.0, -0.0, -0.0,
			-1.0, -1.0,  1.0,	0.0f, 0.0f, 1.0f,	0.0, 0.0,	-1.0, -0.0, -0.0,
			-1.0,  1.0, -1.0,	0.0f, 0.0f, 0.0f,	0.0, 1.0,	-0.0, -0.0, -1.0,
			 1.0, -1.0, -1.0,	0.0f, 1.0f, 1.0f,	1.0, 0.0,	-0.0, -0.0, -1.0,
			-1.0, -1.0, -1.0,	1.0f, 1.0f, 0.0f,	0.0, 0.0,	-0.0, -0.0, -1.0,
			 1.0,  1.0, -1.0,	1.0f, 0.0f, 1.0f,	1.0, 1.0,	 1.0, -0.0, -0.0,
			 1.0, -1.0,  1.0,	1.0f, 1.0f, 1.0f,	0.0, 0.0,	 1.0, -0.0, -0.0,
			 1.0, -1.0, -1.0,	0.0f, 0.0f, 1.0f,	1.0, 0.0,	 1.0, -0.0, -0.0,
			 1.0,  1.0,  1.0,	1.0f, 0.0f, 1.0f,	1.0, 1.0,	-0.0, -0.0,  1.0,
			-1.0, -1.0,  1.0,	1.0f, 0.0f, 1.0f,	0.0, 0.0,	-0.0, -0.0,  1.0,
			 1.0, -1.0,  1.0,	1.0f, 1.0f, 0.0f,	1.0, 0.0,	-0.0, -0.0,  1.0,
			 1.0, -1.0, -1.0,	1.0f, 1.0f, 0.0f,	1.0, 1.0,	-0.0, -1.0, -0.0,
			-1.0, -1.0,  1.0,	1.0f, 1.0f, 0.0f,	0.0, 0.0,	-0.0, -1.0, -0.0,
			-1.0, -1.0, -1.0,	1.0f, 0.0f, 0.0f,	0.0, 1.0,	-0.0, -1.0, -0.0,
			-1.0,  1.0, -1.0,	1.0f, 0.0f, 0.0f,	0.0, 1.0,	-0.0,  1.0, -0.0,
			 1.0,  1.0,  1.0,	1.0f, 0.0f, 1.0f,	1.0, 0.0,	-0.0,  1.0, -0.0,
			 1.0,  1.0, -1.0,	0.0f, 0.0f, 1.0f,	1.0, 1.0,	-0.0,  1.0, -0.0,
			-1.0,  1.0, -1.0,	0.0f, 1.0f, 1.0f,	1.0, 1.0,	-1.0, -0.0, -0.0,
			 1.0,  1.0, -1.0,	0.0f, 1.0f, 1.0f,	1.0, 1.0,	-0.0, -0.0, -1.0,
			 1.0,  1.0,  1.0,	0.0f, 1.0f, 1.0f,	0.0, 1.0,	 1.0, -0.0, -0.0,
			-1.0,  1.0,  1.0,	0.0f, 1.0f, 1.0f,	0.0, 1.0,	-0.0, -0.0,  1.0,
			 1.0, -1.0,  1.0,	1.0f, 1.0f, 1.0f,	1.0, 0.0,	-0.0, -1.0, -0.0,
			-1.0,  1.0,  1.0,	1.0f, 1.0f, 1.0f,	0.0, 0.0,	-0.0,  1.0, -0.0
		
		};

		GLuint indices[12 * 3] =
		{
			0,  1,  2, 
			3,  4,  5, 
			6,  7,  8, 
			9,  10, 11, 
			12, 13, 14, 
			15, 16, 17, 
			0,  18, 1, 
			3,  19, 4, 
			6,  20, 7, 
			9,  21, 10, 
			12, 22, 13, 
			15, 23, 16
		};

		std::unique_ptr<SGLR::shader> shaders;

		std::unique_ptr<SGLR::vertexarray> vao;
		std::unique_ptr<SGLR::vertexbuffer> vbo;
		std::unique_ptr<SGLR::indexbuffer> ibo;

		std::unique_ptr<SGLR::texture> texture;

		float rotation = 0;
		float rotationSpeed = 0.0f;

		std::unique_ptr<SGLR::camera> camera;


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

			vao->link(*vbo, 0, 3, GL_FLOAT, 11, 0);
			vao->link(*vbo, 1, 3, GL_FLOAT, 11, 3);
			vao->link(*vbo, 2, 2, GL_FLOAT, 11, 6);
			vao->link(*vbo, 3, 3, GL_FLOAT, 11, 8);

			vao->unbind();
			vbo->unbind();
			ibo->unbind();

			texture = std::make_unique<SGLR::texture>("textures/brick/t_brickDiffuse.jpg");

			shaders->enable();
			shaders->setUniformInt("tex0", 0);

			camera = std::make_unique<SGLR::camera>(window.get(), shaders.get());

			// setup camera
			camera->cameraSettings(glm::vec3(0.0f, 0.0f, 5.0f), 45.0f, 100.0f);
			camera->frustumSettings("u_projection", "u_view", glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), 0.1f, 100.0f);
			camera->movementSettings(5.0f, 2.0f, 0.5f);

			camera->setActivationKey(INPUT_KEY_LALT);
			
		}

		void onRender(float deltaTime) override
		{
			
			shaders->enable();
			texture->bind();

			glm::mat4 model = glm::mat4(1.0f);

			rotation += rotationSpeed;

			model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

			camera->updateAspect(glm::vec2(getViewportSize().x, getViewportSize().y));
			camera->updateMatrix();

			shaders->setUniformMat4("u_model", model);

			vao->bind();
			
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

			vao->unbind();

			texture->unbind();
			shaders->disable();

		}

		void onUpdate(float deltaTime) override
		{
			camera->updateMovement(deltaTime);
		}

		void onTick(float deltaTime) override
		{}

		void editWindow() override
		{
			ImGui::SliderFloat("cube rotation speed", &rotationSpeed, 0.0f, 1.0f);
		}

};

int main(int argc, char** argv)
{
	SGLR::Log::Init(); // Initialize logger
	
	renderApp app;
	app.start();
	
	SGLR::Log::Shutdown(); // Destroy

	return 0;
}