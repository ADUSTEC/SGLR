#include "window.h"
#include "../Logging/log.h"

#include "../imgui.h"

#include "../Gui/guihandler.h"

namespace SGLR
{
	sglrwindow::sglrwindow(std::string title, glm::vec2 size)
		: m_title(title), m_size(size)
	{}

	sglrwindow::~sglrwindow()
	{
		gui::destroy();

		SDL_GL_DestroyContext(SDL_GL_GetCurrentContext());
		SDL_DestroyWindow(m_window);
		SDL_Quit(); 
	}

	void sglrwindow::createWindow()
	{
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMEPAD);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		m_window = SDL_CreateWindow(m_title.c_str(), m_size.x, m_size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);

		SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		SDL_GLContext gl_context = SDL_GL_CreateContext(m_window);
		SDL_GL_MakeCurrent(m_window, gl_context);
		SDL_ShowWindow(m_window);
		glViewport(0, 0, m_size.x, m_size.y);

		GLint GlewInitResult = glewInit();
		if (GLEW_OK != GlewInitResult)
		{
			LOG_ERROR("GLEW ERROR: {}", (const char*)glewGetErrorString(GlewInitResult));
			exit(EXIT_FAILURE);
		}

		gui::init(m_window, gl_context);
	}

	void sglrwindow::update()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			gui::processEvents(event);
			if (event.type == SDL_EVENT_QUIT)
				exit(0);
			if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(m_window))
				exit(0);
		}

		gui::update();

		glClear(GL_COLOR_BUFFER_BIT);
	}
}