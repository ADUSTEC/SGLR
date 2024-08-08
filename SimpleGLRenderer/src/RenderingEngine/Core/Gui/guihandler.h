#pragma once

#include <SDL3/SDL.h>
#include "../imgui.h"
#include "../imgui_impl_sdl3.h"
#include "../imgui_impl_opengl3.h"

namespace SGLR
{
	class gui
	{
		public:
			void static processEvents(SDL_Event event)
			{
				ImGui_ImplSDL3_ProcessEvent(&event);
			}

			void static init(SDL_Window* window, SDL_GLContext gl_context);
			void static update();
			void static makeDockSpace();
			void static render();
			void static destroy();
	};
}
