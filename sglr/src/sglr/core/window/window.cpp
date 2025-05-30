#include "sglr/core/window/window.h"
#include "sglr/core/log/log.h"

#include "../imgui.h"

#include "sglr/core/gui/guihandler.h"

namespace sglr
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
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		m_window = SDL_CreateWindow(m_title.c_str(), (int)m_size.x, (int)m_size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
		SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		SDL_GLContext gl_context = SDL_GL_CreateContext(m_window);
		SDL_GL_MakeCurrent(m_window, gl_context);
		SDL_ShowWindow(m_window);
		glViewport(0, 0, (GLsizei)m_size.x, (GLsizei)m_size.y);

		GLint GlewInitResult = glewInit();
		if (GLEW_OK != GlewInitResult)
		{
			LOG_ERROR("GLEW ERROR: {}", (const char*)glewGetErrorString(GlewInitResult));
			exit(EXIT_FAILURE);
		}

		gui::init(m_window, gl_context);

		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		
	}

	void sglrwindow::update()
	{
		int width;
		int height;
		SDL_GetWindowSize(m_window, &width, &height);

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			gui::processEvents(event);
			if (event.type == SDL_EVENT_QUIT)
				exit(0);
			if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(m_window))
				exit(0);
			if (event.type == SDL_EVENT_WINDOW_RESIZED)
				m_size.x = (float)width;
				m_size.y = (float)height;
		}

		gui::update();
	}
}