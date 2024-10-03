#include "sglr/Graphics/Renderer/camera.h"

namespace sglr
{

	camera::camera(sglrwindow* window, shader* shader)
	{
		m_window = window;
		m_shader = shader;
	}

	// settings
	void camera::cameraSettings(glm::vec3 position, float fov, float sensitivity, const char* ucamerapositionname)
	{
		m_position = position;
		m_fov = fov;
		m_sensitivity = sensitivity;
		m_ucamerapositionname = ucamerapositionname;
	}

	void camera::frustumSettings(const char* uprojectionname, const char* uviewname, glm::vec3 upvector, glm::vec3 forwardvector, float nearplane, float farplane)
	{
		m_uprojectionname = uprojectionname;
		m_uviewname = uviewname;
		m_upvector = upvector;
		m_forwardvector = forwardvector;
		m_nearplane = nearplane;
		m_farplane = farplane;
	}

	void camera::movementSettings(float speed, float speedmultmax, float speedmultmin)
	{
		m_setspeed = speed;
		m_speedmultmax = speedmultmax;
		m_speedmultmin = speedmultmin;
	}

	// updating
	
	void camera::updateMovement(float deltatime)
	{
		if (keyboard::key(INPUT_KEY_LALT))
		{
			// MOVEMENT
			switch (keyboard::key(INPUT_KEY_W))
			{
			case true:
				m_position += (m_speed * deltatime) * m_forwardvector;
				break;
			}

			switch (keyboard::key(INPUT_KEY_S))
			{
			case true:
				m_position += (m_speed * deltatime) * -m_forwardvector;
				break;
			}

			switch (keyboard::key(INPUT_KEY_A))
			{
			case true:
				m_position += (m_speed * deltatime) * -m_rightvector;
				break;
			}


			switch (keyboard::key(INPUT_KEY_D))
			{
			case true:
				m_position += (m_speed * deltatime) * m_rightvector;
				break;
			}


			// UP & DOWN
			switch (keyboard::key(INPUT_KEY_E))
			{
			case true:
				m_position += (m_speed * deltatime) * m_upvector;
				break;
			}

			switch (keyboard::key(INPUT_KEY_Q))
			{
			case true:
				m_position += (m_speed * deltatime) * -m_upvector;
				break;
			}

			// SPEED
			switch (keyboard::key(INPUT_KEY_LSHIFT))
			{
			case true:
				m_speed = m_setspeed * m_speedmultmax;
				break;
			}
			switch (keyboard::key(INPUT_KEY_LCTRL))
			{
			case true:
				m_speed = m_setspeed * m_speedmultmin;
				break;
			}
			switch (!keyboard::key(INPUT_KEY_LSHIFT) && !keyboard::key(INPUT_KEY_LCTRL))
			{
			case true:
				m_speed = m_setspeed;
				break;
			}

		}

		// ROTATION
		if (keyboard::key(INPUT_KEY_LALT))
		{
			mouse::lock();
			if (mouse::button(INPUT_MOUSE_LEFT))
			{
				if (m_isinitialclick)
				{
					mouse::setPosInWindow(m_window->returnSDLWindow(), (m_window->returnSize().x / 2), (m_window->returnSize().y / 2));
					m_isinitialclick = false;
				}

				float rotX = m_sensitivity * (float)(mouse::y() - (m_window->returnSize().y / 2)) / m_window->returnSize().y;
				float rotY = m_sensitivity * (float)(mouse::x() - (m_window->returnSize().x / 2)) / m_window->returnSize().x;
				
				glm::vec3 newOrientation = glm::rotate(m_forwardvector, glm::radians(-rotX), m_rightvector);

				if (abs(glm::angle(newOrientation, m_upvector) - glm::radians(90.0f)) <= glm::radians(85.0f))
				{
					m_forwardvector = newOrientation;
				}

				m_forwardvector = glm::rotate(m_forwardvector, glm::radians(-rotY), m_upvector);
				m_rightvector = glm::normalize(glm::cross(m_forwardvector, m_upvector));

			}
			mouse::setPosInWindow(m_window->returnSDLWindow(), (m_window->returnSize().x / 2), (m_window->returnSize().y / 2));

			
		}
		else
		{
			mouse::unlock();
			m_isinitialclick = true;
		}
	
	}
	
	void camera::updateAspect(glm::vec2 aspect)
	{
		m_aspect = aspect;
	}
	
	void camera::updateGCS()
	{
		m_view = glm::lookAt(m_position, m_position + m_forwardvector, m_upvector);
		m_projection = glm::perspective(glm::radians(m_fov), (float)(m_aspect.x / m_aspect.y), m_nearplane, m_farplane);

		m_shader->setUniformMat4(m_uprojectionname, m_projection);
		m_shader->setUniformMat4(m_uviewname, m_view);

		m_shader->setUniformVec3("u_camerapos", getPosition());
	}

}