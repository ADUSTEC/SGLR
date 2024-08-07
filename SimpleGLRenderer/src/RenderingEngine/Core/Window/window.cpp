#include "window.h"

#include "../imgui.h"
#include "../imgui_impl_sdl3.h"
#include "../imgui_impl_opengl3.h"

namespace SGLR
{
	sglrwindow::sglrwindow(std::string title, glm::vec2 size)
		: m_title(title), m_size(size)
	{
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMEPAD);
		IMGUI_CHECKVERSION();
		glewInit();
	}

	sglrwindow::~sglrwindow()
	{
		ImGui_ImplOpenGL3_Shutdown(); 
		ImGui_ImplSDL3_Shutdown();  
		ImGui::DestroyContext(); 

		SDL_GL_DestroyContext(SDL_GL_GetCurrentContext());
		SDL_DestroyWindow(m_window);
		SDL_Quit(); 
	}

	void sglrwindow::createWindow()
	{
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		m_window = SDL_CreateWindow(m_title.c_str(), m_size.x, m_size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);

		SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		SDL_GLContext gl_context = SDL_GL_CreateContext(m_window);
		SDL_GL_MakeCurrent(m_window, gl_context);
		SDL_ShowWindow(m_window);
		glViewport(0, 0, m_size.x, m_size.y);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext(); 
		ImGui_ImplSDL3_InitForOpenGL(m_window, gl_context);
		ImGui_ImplOpenGL3_Init("#version 130"); 
	}

	void sglrwindow::update()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL3_ProcessEvent(&event);
			if (event.type == SDL_EVENT_QUIT)
				exit(0);
			if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(m_window))
				exit(0);
		}
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();
	}
}