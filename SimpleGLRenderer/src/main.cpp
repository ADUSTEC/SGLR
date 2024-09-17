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

		std::unique_ptr<SGLR::texture> diffusetexture;
		std::unique_ptr<SGLR::texture> speculartexture;

		float rotation = 0;
		float rotationSpeed = 0.0f;

		std::unique_ptr<SGLR::camera> camera;

		glm::vec3 lightposition = glm::vec3(3.0f, 4.0f, 2.0f);
		glm::vec3 lightcolor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 angle = glm::vec3(0.0f, 1.0f, 0.0f);

		int lightmode = 1;


	public:
		renderApp() {}
		~renderApp() 
		{
			vao->destroy();
			vbo->destroy();
			ibo->destroy();
			shaders->destroy();
			diffusetexture->destroy();
			speculartexture->destroy();
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

			diffusetexture = std::make_unique<SGLR::texture>("textures/brick/t_brickDiffuse.jpg", 0);
			diffusetexture->textureIndex(shaders.get(), "u_material.diffuse", 0);

			speculartexture = std::make_unique<SGLR::texture>("textures/brick/t_brickRoughness.jpg", 1);
			speculartexture->textureIndex(shaders.get(), "u_material.specular", 1);

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

			diffusetexture->bind();
			speculartexture->bind();

			glm::mat4 model = glm::mat4(1.0f);

			rotation += rotationSpeed;

			model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

			camera->updateAspect(glm::vec2(getViewportSize().x, getViewportSize().y));
			camera->updateMatrix();

			shaders->setUniformMat4("u_model", model);
			shaders->setUniformVec3("u_campos", camera->getPosition());
			
			shaders->setUniformFloat("u_material.shininess", 2.0f);
			
			shaders->setUniformVec3("u_light.position", lightposition); 
			shaders->setUniformVec3("u_light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
			shaders->setUniformVec3("u_light.diffuse", glm::vec3(lightcolor));
			shaders->setUniformVec3("u_light.specular", glm::vec3(0.5f, 0.5f, 0.5f));
			
			shaders->setUniformInt("u_light.lightmode", lightmode);
			
			if (lightmode == 1)
			{
				shaders->setUniformFloat("u_pointlight.constant", 1.0f);
				shaders->setUniformFloat("u_pointlight.quadratic", 0.032f);
				shaders->setUniformFloat("u_pointlight.linear", 0.09f);

				shaders->setUniformFloat("u_pointlight.intensity", 1);
			}
			else if (lightmode == 2)
			{
				shaders->setUniformFloat("u_spotlight.constant", 1.0f);
				shaders->setUniformFloat("u_spotlight.quadratic", 0.032f);
				shaders->setUniformFloat("u_spotlight.linear", 0.09f);
				
				shaders->setUniformVec3("u_spotlight.angle", angle);
				shaders->setUniformFloat("u_spotlight.innercone", glm::cos(glm::radians(12.5f)));
				shaders->setUniformFloat("u_spotlight.outercone", glm::cos(glm::radians(20.5f)));
				shaders->setUniformFloat("u_spotlight.intensity", 5);
			}
			else if (lightmode == 3)
			{
				shaders->setUniformVec3("u_sunlight.angle", angle);
			}

			vao->bind();
			
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

			vao->unbind();
			speculartexture->unbind();
			diffusetexture->bind();
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
			ImGui::SliderFloat("rotate cube", &rotationSpeed, 0.0f, 1.0f);

			ImGui::SeparatorText("Light Type");
			switch (lightmode)
			{
				case 1:
					ImGui::Text("Point Light");
					break;
				case 2:
					ImGui::Text("Spot Light");
					break;
				case 3:
					ImGui::Text("Sun Light");
					break;
				default:
					ImGui::Text("DEFAULT (point)");
					break;
			}
			ImGui::DragInt("type", &lightmode, 1, 1, 3);

			ImGui::SeparatorText("Light Position");
			ImGui::SliderFloat3("XYZ", glm::value_ptr(lightposition), 0.0f, 10.0f);

			ImGui::SeparatorText("Light Angle");
			ImGui::SliderFloat3("RPY", glm::value_ptr(angle), -1.0f, 1.0f);

			ImGui::ColorPicker3("Light Color", glm::value_ptr(lightcolor));
		}

		void materialWindow() override
		{
			
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