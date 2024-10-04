#pragma once
#include <glm.hpp>
#include "camera.h"
#include "../shader.h"

namespace sglr
{
	// DATA STRUCTURES
	struct pointlightdata
	{
		glm::vec3 pl_position;

		glm::vec3 pl_diffuse;
		glm::vec3 pl_specular;

		float pl_constant;
		float pl_quadratic;
		float pl_linear;

		float pl_intensity;

		pointlightdata(
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
			glm::vec3 diffuse = glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f),
			float constant = 1.0f, 
			float quadratic = 0.032f, 
			float linear = 0.09f, 
			float intensity = 1.0f)
			: pl_position(position), pl_diffuse(diffuse), pl_specular(specular), pl_constant(constant), pl_quadratic(quadratic), pl_linear(linear), pl_intensity(intensity) 
		{}
	};
	struct spotlightdata
	{
		glm::vec3 sp_position;

		glm::vec3 sp_diffuse;
		glm::vec3 sp_specular;

		float sp_constant;
		float sp_quadratic;
		float sp_linear;

		glm::vec3 sp_angle;
		float sp_innercone;
		float sp_outercone;
		float sp_intensity;

		spotlightdata(
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 diffuse = glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f),
			float constant = 1.0f,
			float quadratic = 0.032f,
			float linear = 0.09f,
			glm::vec3 angle = glm::vec3(0.0f, -1.0f, 0.0f),
			float innercone = glm::cos(glm::radians(5.5f)),
			float outercone = glm::cos(glm::radians(15.5f)),
			float intensity = 1.0f)

			: 

			sp_position(position), 
			sp_diffuse(diffuse), 
			sp_specular(specular), 
			sp_constant(constant), 
			sp_quadratic(quadratic), 
			sp_linear(linear), 
			sp_angle(angle), 
			sp_innercone(innercone), 
			sp_outercone(outercone), 
			sp_intensity(intensity)
		{}
	};
	struct sunlightdata
	{
		glm::vec3 s_angle;

		glm::vec3 s_diffuse;
		glm::vec3 s_specular;

		sunlightdata(
			glm::vec3 angle = glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3 diffuse = glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f))
			: s_angle(angle), s_diffuse(diffuse), s_specular(specular)
		{}
	};

	class scenelight
	{
	public:
		scenelight(camera* camera, shader* shader,
			const char* uplight = "u_pointlight",
			const char* usplight = "u_spotlight",
			const char* uslight = "u_sunlight")
			: m_camera(camera), m_shader(shader) 
		{
			if (!m_init())
			{
				LOG_ERROR("SCENELIGHT ERROR: FAILED TO INITIALIZE SCENELIGHT");
			}
		}

		~scenelight()
		{
			delete m_camera;
			delete m_shader;
		}

		void newPointLight(int index, const pointlightdata* data = &pointlightdata());
		void newSpotLight(int index, const spotlightdata* data = &spotlightdata());
		void createSunLight(const sunlightdata* data = &sunlightdata());
		void setGlobalAmbientLight(glm::vec3 value);

		void deleteAllPointLights();
		void deleteAllSpotLights();
		void deleteSunLight();

		pointlightdata getPointLightData(int index);
		spotlightdata getSpotLightData(int index);
		sunlightdata getSunLightData(int index);

		void editPointLightData(int index, const pointlightdata& data);
		void editSpotLightData(int index, const spotlightdata& data);
		void editSunLightData(const sunlightdata& data);

		void updateScenePointLight(int index);
		void updateSceneSpotLight(int index);
		void updateSceneSunLight();
	private:
		
		bool m_init() { return false; }

		shader* m_shader;
		camera* m_camera;

		std::vector<int> pl_inscene;
		std::vector<int> sp_inscene;
		std::vector<int> s_inscene;

		std::vector<pointlightdata> m_pointlightdata;
		std::vector<spotlightdata> m_spotlightdata;
		std::vector<sunlightdata> m_sunlightdata;
	};
	
}