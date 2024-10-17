#include "sglr/sglr.h"
#include "sglr/graphics/renderer/scenelight.h"

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

		std::unique_ptr<sglr::scenelight> scenelight;

		sglr::spotlightdata spotlight = sglr::spotlightdata(
															glm::vec3(-2.900, 3.400, 2.350), 
															glm::vec3(0.800, -1.000, -0.700), 
															glm::vec3(255/255.0f, 151/255.0f, 27/255.0f),
															0.995f,
															0.964f);


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

			scenelight = std::make_unique<sglr::scenelight>(shader.get());

			scenelight->newSpotLight();
			
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
			
			scenelight->updateAllLights();
			

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

			ImGui::SeparatorText("CONFIGURE SPOTLIGHT");
			ImGui::DragFloat3("Position", glm::value_ptr(spotlight.sp_position), 0.05f, -20.0f, 20.0f);
			ImGui::DragFloat3("Angle", glm::value_ptr(spotlight.sp_angle), 0.05f, -1.0f, 1.0f);

			ImGui::DragFloat("Innercone Size", &spotlight.sp_innercone, 0.005f, glm::cos(glm::radians(0.0f)), glm::cos(glm::radians(50.0f)));
			ImGui::DragFloat("Outercone Size", &spotlight.sp_outercone, 0.005f, glm::cos(glm::radians(0.0f)), glm::cos(glm::radians(50.0f)));

			ImGui::ColorEdit3("Diffuse Color", glm::value_ptr(spotlight.sp_diffuse));

			ImGui::TextDisabled("-- ANISOTROPY");
			ImGui::DragFloat("Constant", &spotlight.sp_constant, 0.05f, 0.0f, 10.0f);
			ImGui::DragFloat("Quadratic", &spotlight.sp_quadratic, 0.05f, 0.0f, 10.0f);
			ImGui::DragFloat("Linear", &spotlight.sp_linear, 0.05f, 0.0f, 10.0f);

			ImGui::DragFloat("Intensity", &spotlight.sp_intensity, 0.05f, 0.0f, 10.0f);

			ImGui::TextDisabled("intensity doesnt work as intended, will fix later");

			scenelight->editSpotLight(0, spotlight);

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