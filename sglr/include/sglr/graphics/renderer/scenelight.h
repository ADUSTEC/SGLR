#pragma once
#include <glm.hpp>
#include "camera.h"
#include "../shader.h"

// there is definitely a better way of doing this but this was an easy solution

namespace sglr
{
	// DATA STRUCTURES
	struct pointlightdata
	{
		glm::vec3 pl_position;

		glm::vec3 pl_diffuse;

		float pl_constant;
		float pl_quadratic;
		float pl_linear;

		float pl_intensity;

		pointlightdata(
			glm::vec3 position = glm::vec3(0.0f, 1.1f, 0.0f),
			glm::vec3 diffuse = glm::vec3(1.0f, 1.0f, 1.0f),
			float constant = 1.0f,
			float quadratic = 0.032f,
			float linear = 0.09f,
			float intensity = 1.0f)
			: pl_position(position), pl_diffuse(diffuse), pl_constant(constant), pl_quadratic(quadratic), pl_linear(linear), pl_intensity(intensity)
		{}
	};
	
	struct spotlightdata
	{
		glm::vec3 sp_position;

		glm::vec3 sp_diffuse;

		float sp_constant;
		float sp_quadratic;
		float sp_linear;

		glm::vec3 sp_angle;
		float sp_innercone;
		float sp_outercone;
		float sp_intensity;

		spotlightdata(
			glm::vec3 position = glm::vec3(0.0f, 1.1f, 0.0f),
			glm::vec3 angle = glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3 diffuse = glm::vec3(1.0f, 1.0f, 1.0f),
			float innercone = glm::cos(glm::radians(5.5f)),
			float outercone = glm::cos(glm::radians(15.5f)),
			float constant = 1.0f,
			float quadratic = 0.032f,
			float linear = 0.09f,
			float intensity = 1.0f)

			:

			sp_position(position),
			sp_diffuse(diffuse),
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

		sunlightdata(
			glm::vec3 angle = glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3 diffuse = glm::vec3(1.0f, 1.0f, 1.0f)
		)
			: s_angle(angle), s_diffuse(diffuse)
		{}
	};

	class scenelight
	{
	public:
		scenelight(shader* shader,
			const char* uplight = "u_pointlight",
			const char* usplight = "u_spotlight",
			const char* uslight = "u_sunlight")
			: m_uplight(uplight), m_usplight(usplight), m_uslight(uslight)
		{
			if (!m_init(shader))
			{
				LOG_ERROR("SCENELIGHT ERROR: FAILED TO INITIALIZE SCENELIGHT");
			}
		}

		~scenelight()
		{
			delete m_shader;
		}

		void newPointLight(const pointlightdata data = pointlightdata());
		void newSpotLight(const spotlightdata data = spotlightdata());
		void createSunLight(const sunlightdata data = sunlightdata());

		void setGlobalAmbientLight(glm::vec3 value)
		{
			m_globalambient = value;
		}

		void revertAllPointLights();
		void revertAllSpotLights();
		void revertSunLight();


		void updateScenePointLights();
		void updateSceneSpotLights();
		void updateSceneSunLight();

		void updateAllLights()
		{
			updateScenePointLights();
			updateSceneSpotLights();
			updateSceneSunLight();
		}

		void editPointLight(int index, pointlightdata data) { m_pl[index] = data; }
		void editSpotLight(int index, spotlightdata data) { m_sp[index] = data; }
		void editSunLight(sunlightdata data) { m_s = data; }
	private:

		bool m_init(shader* shader);

		shader* m_shader;

		pointlightdata m_pl[50];
		spotlightdata m_sp[50];
		sunlightdata m_s;
		
		const char* m_uplight;
		const char* m_usplight;
		const char* m_uslight;

		glm::vec3 m_globalambient = glm::vec3(0.05f, 0.05f, 0.05f);
		
		int m_plIndex = 0;
		int m_spIndex = 0;
		int m_sIndex = 0;

		std::string pl_uposname;
		std::string pl_udifname;
		std::string pl_uconname;
		std::string pl_uquaname;
		std::string pl_ulinname;
		std::string pl_uintname;

		std::string sp_uposname;
		std::string sp_uangname;
		std::string sp_uinnname;
		std::string sp_uoutname;
		std::string sp_udifname;
		std::string sp_uconname;
		std::string sp_uquaname;
		std::string sp_ulinname;
		std::string sp_uintname;

		std::string s_uangname;
		std::string s_udifname;

	};
	
}