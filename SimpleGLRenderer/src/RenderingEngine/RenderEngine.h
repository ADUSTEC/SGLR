#include "Core/Logging/log.h"
#include "Tools/clock.h"
#include "Core/Window/window.h"
#include "Core/Gui/guihandler.h"

#include <iostream>
#include <string>
#include <vec2.hpp>
#include "../imgui_impl_sdl3.h"
#include "../imgui_impl_opengl3.h"

// Application will be used by main by creating a custom class that inherits from Application
namespace SGLR {
	class Application
	{
		public:
			// simply starts the application once called
			void start()
			{
				onInit(); // call before run
				m_run(); // start app
			} 

		protected:
			Application() 
				: m_fps(0), m_ups(0), deltaUpdateTime(0), deltaRenderTime(0), deltaTickTime(0)
			{
				m_window = std::unique_ptr<sglrwindow>(new sglrwindow("SGLR", glm::vec2(1600, 900)));
			}

			virtual ~Application() { }

			virtual void onInit() = 0; // called one time when the start function is called

			virtual void onRender(float deltaTime) = 0; // called every frame
			virtual void onTick(float deltaTime) = 0; // called for each tick
			virtual void onUpdate(float deltaTime) = 0; // called for each update
			
			// return func
			const UINT getFPS() const { return m_fps; }
			const UINT getUPS() const { return m_ups; }

		private:
			// runs once the start function is called
			void m_run() 
			{
				float timer = 0.0f;
				float updateTimer = 0.0f;
				float updateTick = 1.0f / 240.0f;
				unsigned int frames = 0;
				unsigned int updates = 0;

				
				m_window.get()->createWindow();

				// while the application is running; handle the update, tick and render functions.
				while (true)
				{
					m_window.get()->update();
					if (m_window.get()->minimized())
					{
						SDL_Delay(10);
						continue;
					}

					if (m_clock.elapsed() - updateTimer > updateTick)
					{
						deltaUpdateTime = m_deltaUpdate.elapsed();
						onUpdate(deltaUpdateTime);
						updates++;
						updateTimer += updateTick;
						m_deltaUpdate.restart();
					}

					frames++;
					if (m_clock.elapsed() - timer > 1.0f)
					{
						deltaTickTime = m_deltaTick.elapsed();
						timer += 1.0f;
						m_fps = frames;
						m_ups = updates;
						frames = 0;
						updates = 0;
						onTick(deltaTickTime);
						m_deltaTick.restart();
					}

					 
					glClearColor(0.6f, 0.3f, 0.1f, 1.0f);

					gui::makeDockSpace();
					onRender(deltaRenderTime);
					gui::render();
					
					m_window.get()->swap();

					deltaRenderTime = m_deltaRender.elapsed();
					m_deltaRender.restart();
				}
			}

			// window
			std::unique_ptr<sglrwindow> m_window;

			// individual deltatime variables
			float deltaUpdateTime = 0;
			float deltaRenderTime = 0;
			float deltaTickTime = 0;
			
			// Clock variables
			Clock m_clock;
			Clock m_deltaRender;
			Clock m_deltaUpdate;
			Clock m_deltaTick;

			UINT m_fps = 0, m_ups = 0; // frames per sec + updates per sec variables
	};
}