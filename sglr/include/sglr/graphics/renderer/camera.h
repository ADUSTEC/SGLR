#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include<GL/glew.h>

#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include<gtx/rotate_vector.hpp>
#include<gtx/vector_angle.hpp>

#include "../../core/input/keyboard.h"
#include "../../core/input/mouse.h"
#include "../shader.h"

#include "../../core/window/window.h"
#include "../imgui.h"

namespace sglr
{
	// ideally all movement should be handled by the camera class, so external control is not available.
	class camera
	{
	public:
		camera(sglrwindow* window, shader* shader);
		~camera() 
		{
			delete m_window;
			delete m_shader;
		}

		// settings functions
		void cameraSettings(glm::vec3 position = glm::vec3(0.0f, 1.0f, 6.0f), float fov = 45.0f, float sensitivity = 100.0f, const char* ucamerapositionname = "u_camerapos");

		void frustumSettings
		(	// had too many input arguments so its formatted like this
			const char* uprojectionname = "u_projection",
			const char* uviewname = "u_view",
			glm::vec3 upvector = glm::vec3(0.0f, 1.0f, 0.0f), 
			glm::vec3 forwardvector = glm::vec3(0.0f, 0.0f, -1.0f),
			float nearplane = 0.01f, 
			float farplane = 100.0f
		);
		
		void movementSettings(float speed = 5.0f, float speedmultmax = 2.0f, float speedmultmin = 0.5f);

		// update functions
		void updateAspect(glm::vec2 aspect);
		void updateGCS(); // update given camera shaders
		void updateMovement(float deltatime);
		
		// set
		void setActivationKey(KEYINPUTCODES inputcode = INPUT_KEY_LALT) { m_activationkey = inputcode; }

		// getters
		glm::mat4 getProjection() { return m_projection; }
		glm::mat4 getView() { return m_view; }

		glm::vec3 getPosition() { return m_position; }

		glm::vec3 getForwardVector() { return m_forwardvector; }
		glm::vec3 getUpVector() { return m_upvector; }
		glm::vec3 getRightVector() { return m_rightvector; }

		glm::vec2 getAspect() { return m_aspect; }

	private:
		sglrwindow* m_window{};
		shader* m_shader{};

		const char* m_uprojectionname = "u_projection";
		const char* m_uviewname = "u_view";

		const char* m_ucamerapositionname = "u_camerapos";

		glm::vec2 m_aspect = glm::vec2(NULL, NULL);

		glm::vec3 m_position = glm::vec3(0.0f, 1.0f, 6.0f);
		glm::vec3 m_forwardvector = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_upvector = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_rightvector = glm::normalize(glm::cross(m_forwardvector, m_upvector));

		glm::mat4 m_projection = glm::mat4(1.0f);
		glm::mat4 m_view = glm::mat4(1.0f);

		float m_nearplane = 0.01f;
		float m_farplane = 100.0f;

		float m_fov = 45.0f;
		float m_sensitivity = 100.0f;
		float m_setspeed = 5.0f;
		float m_speed = NULL;
		float m_speedmultmax = 2.0f;
		float m_speedmultmin = 0.5f;

		KEYINPUTCODES m_activationkey = INPUT_KEY_LALT;

		bool m_isinitialclick = false;
	};
}