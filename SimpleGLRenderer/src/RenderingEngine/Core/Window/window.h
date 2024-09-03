#pragma once

#include <gl/glew.h>
#include <SDL3/SDL.h>
#include <vec2.hpp>
#include <string>

namespace SGLR
{
	class sglrwindow
	{
		public:
			sglrwindow(std::string title, glm::vec2 size);
			~sglrwindow();

			void createWindow();
			void update();
			void swap()
			{
				SDL_GL_SwapWindow(m_window); // swap gl buffers
			}
			bool minimized()
			{
				if (SDL_GetWindowFlags(m_window) & SDL_WINDOW_MINIMIZED) // used for limiting resources when window is minimized
					return true;
				else
					return false;
			}

			SDL_Window* returnSDLWindow()
			{
				return m_window;
			}

			glm::vec2 returnSize()
			{
				return m_size;
			}
			

		private:
			std::string m_title;
			glm::vec2 m_size;
			SDL_Window* m_window = nullptr;
	};
}