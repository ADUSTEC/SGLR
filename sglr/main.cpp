#include "sglr/sglr.h"


class renderApp : public sglr::app
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

		std::unique_ptr<sglr::shader> shader;

		std::unique_ptr<sglr::vertexarray> vao;
		std::unique_ptr<sglr::vertexbuffer> vbo;
		std::unique_ptr<sglr::indexbuffer> ibo;

		std::unique_ptr<sglr::texture> diffusetexture;
		std::unique_ptr<sglr::texture> speculartexture;
		std::unique_ptr<sglr::texture> normaltexture;

		float rotation = 0;
		float rotationSpeed = 0.0f;

		std::unique_ptr<sglr::camera> camera;

		glm::vec3 lightposition = glm::vec3(3.0f, 4.0f, 2.0f);
		glm::vec3 lightcolor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 angle = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::vec3 lightposition2 = glm::vec3(-3.0f, -4.0f, -2.0f);
		glm::vec3 lightcolor2 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 angle2 = glm::vec3(0.0f, 1.0f, 0.0f);

		int lightmode = 1;


	public:
		renderApp() {}
		~renderApp() 
		{
			vao->destroy();
			vbo->destroy();
			ibo->destroy();
			shader->destroy();
			diffusetexture->destroy();
			speculartexture->destroy();
			normaltexture->destroy();
		}

		void onInit() override
		{
			shader = std::make_unique<sglr::shader>("shaders/basic_v.glsl", "shaders/basic_f.glsl");

			vao = std::make_unique<sglr::vertexarray>();

			vao->bind();

			vbo = std::make_unique<sglr::vertexbuffer>(vertices, sizeof(vertices));
			ibo = std::make_unique<sglr::indexbuffer>(indices, sizeof(indices));

			ibo->bind();

			vao->link(*vbo, 0, 3, GL_FLOAT, 11, 0);
			vao->link(*vbo, 1, 3, GL_FLOAT, 11, 3);
			vao->link(*vbo, 2, 2, GL_FLOAT, 11, 6);
			vao->link(*vbo, 3, 3, GL_FLOAT, 11, 8);

			vao->unbind();
			vbo->unbind();
			ibo->unbind();

			diffusetexture = std::make_unique<sglr::texture>("textures/brick/t_brickDiffuse.jpg", 0);
			diffusetexture->textureIndex(shader.get(), "u_material.diffuse", 0);

			speculartexture = std::make_unique<sglr::texture>("textures/brick/t_brickRoughness.jpg", 1);
			speculartexture->textureIndex(shader.get(), "u_material.specular", 1);

			normaltexture = std::make_unique<sglr::texture>("textures/brick/t_brickNormal.jpg", 2);
			normaltexture->textureIndex(shader.get(), "u_material.normal", 2);

			camera = std::make_unique<sglr::camera>(window.get(), shader.get());

			// setup camera
			camera->cameraSettings(glm::vec3(0.0f, 0.0f, 5.0f), 45.0f, 100.0f);
			camera->frustumSettings("u_projection", "u_view", glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), 0.1f, 100.0f);
			camera->movementSettings(5.0f, 2.0f, 0.5f);

			camera->setActivationKey(INPUT_KEY_LALT);
			
		}

		void onRender(float deltaTime) override
		{
			
			shader->enable();

			diffusetexture->bind();
			speculartexture->bind();
			normaltexture->bind();

			glm::mat4 model = glm::mat4(1.0f);

			rotation += rotationSpeed;

			model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

			shader->setUniformMat4("u_model", model);

			camera->updateAspect(glm::vec2(getViewportSize().x, getViewportSize().y));
			camera->updateGCS();

			
			shader->setUniformFloat("u_material.shininess", 2.0f);

			shader->setUniformInt("pointlightnum", 2);
			shader->setUniformVec3("u_globalambient", glm::vec3(0.05f, 0.05f, 0.05f));

			shader->setUniformVec3("u_pointlight[0].position", lightposition); 

			shader->setUniformVec3("u_pointlight[0].diffuse", glm::vec3(lightcolor));
			shader->setUniformVec3("u_pointlight[0].specular", glm::vec3(0.5f, 0.5f, 0.5f));

			shader->setUniformFloat("u_pointlight[0].constant", 1.0f);
			shader->setUniformFloat("u_pointlight[0].quadratic", 0.032f);
			shader->setUniformFloat("u_pointlight[0].linear", 0.09f);

			shader->setUniformFloat("u_pointlight[0].intensity", 1);

			// light 2
			shader->setUniformVec3("u_pointlight[1].position", lightposition2);

			shader->setUniformVec3("u_pointlight[1].diffuse", glm::vec3(lightcolor2));
			shader->setUniformVec3("u_pointlight[1].specular", glm::vec3(0.5f, 0.5f, 0.5f));

			shader->setUniformFloat("u_pointlight[1].constant", 1.0f);
			shader->setUniformFloat("u_pointlight[1].quadratic", 0.032f);
			shader->setUniformFloat("u_pointlight[1].linear", 0.09f);

			shader->setUniformFloat("u_pointlight[1].intensity", 1);
			
			// spotlight
			/*
			shader->setUniformVec3("u_spotlight[0].position", camera->getPosition());
			shader->setUniformVec3("u_spotlight[0].angle", camera->getForwardVector());

			shader->setUniformVec3("u_spotlight[0].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
			shader->setUniformVec3("u_spotlight[0].specular", glm::vec3(0.5f, 0.5f, 0.5f));

			shader->setUniformFloat("u_spotlight[0].constant", 1.0f);
			shader->setUniformFloat("u_spotlight[0].quadratic", 0.032f);
			shader->setUniformFloat("u_spotlight[0].linear", 0.09f);

			shader->setUniformFloat("u_spotlight[0].innercone", glm::cos(glm::radians(5.5f)));
			shader->setUniformFloat("u_spotlight[0].outercone", glm::cos(glm::radians(15.5f)));
			shader->setUniformFloat("u_spotlight[0].intensity", 5);

			// sunlight
			shader->setUniformVec3("u_spotlight[0].angle", glm::vec3(0, 0, 0));

			shader->setUniformVec3("u_spotlight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
			shader->setUniformVec3("u_spotlight[0].specular", glm::vec3(0.5f, 0.5f, 0.5f));
			*/

			vao->bind();
			
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

			vao->unbind();
			normaltexture->unbind();
			speculartexture->unbind();
			diffusetexture->bind();
			shader->disable();

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

			ImGui::SliderFloat3("XYZ_1", glm::value_ptr(lightposition), -10.0f, 10.0f);
			ImGui::SliderFloat3("XYZ_2", glm::value_ptr(lightposition2), -10.0f, 10.0f);

			ImGui::SliderFloat3("RPY_1", glm::value_ptr(angle), -1.0f, 1.0f);
			ImGui::SliderFloat3("RPY_2", glm::value_ptr(angle2), -1.0f, 1.0f);

			ImGui::ColorPicker3("COLOR_1", glm::value_ptr(lightcolor));
			ImGui::ColorPicker3("COLOR_2", glm::value_ptr(lightcolor2));
		}
		
		void materialWindow() override
		{
			
		}

};

int main(int argc, char** argv)
{
	sglr::log::init(); // Initialize logger
	
	renderApp app;
	app.start();
	
	sglr::log::shutdown(); // Destroy

	return 0;
}