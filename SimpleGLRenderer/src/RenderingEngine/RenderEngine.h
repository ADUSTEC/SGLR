#pragma once
#include "Core/Input/keyboard.h"
#include "Core/Input/mouse.h"
#include "Core/Logging/log.h"
#include "Core/Window/window.h"
#include "Core/Gui/guihandler.h"
#include "Tools/clock.h"
#include "Tools/readfile.h"
#include "RenderingEngine/Graphics/shader.h"
#include "RenderingEngine/Graphics/vertexbuffer.h"
#include "RenderingEngine/Graphics/vertexarray.h"
#include "RenderingEngine/Graphics/indexbuffer.h"
#include "RenderingEngine/Graphics/framebuffer.h"
#include "RenderingEngine/Graphics/Renderer/texture.h"
#include "RenderingEngine/Graphics/Renderer/camera.h"

#include <iostream>
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
				window->createWindow(); // create window, must be done before initialization
				gui::setupStyle(); // runs style function
				onInit(); // call before run
				m_run(); // start app
			} 

		protected:
			Application() 
				: m_fps(0), m_ups(0), deltaUpdateTime(0), deltaRenderTime(0), deltaTickTime(0)
			{
				window = std::unique_ptr<sglrwindow>(new sglrwindow("SGLR", glm::vec2(1600, 900)));
			}

			virtual ~Application() { }

			virtual void onInit() = 0; // called one time when the start function is called

			virtual void onRender(float deltaTime) = 0; // called every frame
			virtual void onTick(float deltaTime) = 0; // called for each tick
			virtual void onUpdate(float deltaTime) = 0; // called for each update

			virtual void editWindow() = 0; // ran inside of the edit window
			
			// return func
			const UINT getFPS() { return m_fps; }
			const UINT getUPS() { return m_ups; }

			const glm::vec2 getViewportSize() { return m_viewportSize; }

			// window
			std::unique_ptr<sglrwindow> window;

		private:
			glm::vec2 m_viewportSize;

			// runs once the start function is called
			void m_run() 
			{
				float timer = 0.0f;
				float updateTimer = 0.0f;
				float updateTick = 1.0f / 240.0f;
				UINT frames = 0;
				UINT updates = 0;
				
				glClearColor(0.03229527175426483f, 0.04749304801225662f, 0.0784313753247261f, 1.0f);

				keyboard::init();
				mouse::init();

				// while the application is running; handle the update, tick and render functions.
				while (true)
				{
					framebuffer viewport(window->returnSize());
					window->update();
					keyboard::update();
					mouse::update();

					glClear(GL_COLOR_BUFFER_BIT);

					if (window->minimized())
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

					gui::makeDockSpace();

					ImGui::Begin("Outliner");
					{
						// Centering using https://github.com/ocornut/imgui/discussions/3862 - unexpectedly worked perfect without any changes somehow
						ImGuiStyle& style = ImGui::GetStyle();
						float width = 0.0f;
						width += ImGui::CalcTextSize("Hello").x;
						width += style.ItemSpacing.x;
						width += 150.0f;
						width += style.ItemSpacing.x;
						width += ImGui::CalcTextSize("World!").x;

						float avail = ImGui::GetContentRegionAvail().x;
						float off = (avail - width) * 0.5f;
						if (off > 0.0f)
							ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
						/////////////////////////////////////////////////////////////////////////////

						if (ImGui::Button("Add Primitive"))
							ImGui::OpenPopup("primitive_popup");

						ImGui::SameLine();

						if (ImGui::Button("Import Mesh"))
							ImGui::OpenPopup("mesh_popup");

						if (ImGui::BeginPopup("primitive_popup", ImGuiWindowFlags_MenuBar))
						{
							if (ImGui::BeginMenuBar())
							{
								ImGui::TextDisabled("Primitives");
								ImGui::EndMenuBar();
							}


							if (ImGui::Selectable("Cube"))		ImGui::CloseCurrentPopup();
							if (ImGui::Selectable("Plane"))		ImGui::CloseCurrentPopup();
							if (ImGui::Selectable("Cylinder"))	ImGui::CloseCurrentPopup();
							if (ImGui::Selectable("Cone"))		ImGui::CloseCurrentPopup();
							if (ImGui::Selectable("Sphere"))	ImGui::CloseCurrentPopup();
							if (ImGui::Selectable("Capsule"))	ImGui::CloseCurrentPopup();
							if (ImGui::Selectable("Torus"))		ImGui::CloseCurrentPopup();

							ImGui::EndPopup();
						}
						if (ImGui::BeginPopup("mesh_popup", ImGuiWindowFlags_MenuBar))
						{
							if (ImGui::BeginMenuBar())
							{
								ImGui::TextDisabled("Import");
								ImGui::EndMenuBar();
							}

							if (ImGui::Selectable("OBJ"))		ImGui::CloseCurrentPopup();
							if (ImGui::Selectable("FBX"))		ImGui::CloseCurrentPopup();
							if (ImGui::Selectable("GLTF"))		ImGui::CloseCurrentPopup();

							ImGui::EndPopup();
						}

						ImGui::Separator();

						ImGui::BeginChild("OutLinerList");

						ImGui::NewLine();
						ImGui::Indent();
						ImGui::TextDisabled("Outliner has no functionality right now :(");
					}

					ImGui::EndChild();
					ImGui::End();

					ImGui::Begin("Edit");
					editWindow();
					ImGui::End();
					
					ImGui::Begin("Material Editor");
					ImGui::End();

					ImGui::Begin("Viewport");
					{
						ImGui::BeginChild("RenderView");
						m_viewportSize = glm::vec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);

						viewport.bind(); // bind the frame buffer
						viewport.rescale(glm::vec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

						glViewport(0, 0, (GLsizei)ImGui::GetContentRegionAvail().x, (GLsizei)ImGui::GetContentRegionAvail().y);

						// clearing the depth buffer must be done here otherwise nothing will render for some odd reason
						// I assume its something related to how imgui renders the gui but im not entirely sure
						glClear(GL_DEPTH_BUFFER_BIT); 
						onRender(deltaRenderTime); // do rendering

						viewport.unbind(); // unbind the frame buffer

						// display anything rendered to the viewport
						ImGui::Image
						(
							(ImTextureID)viewport.returnFrame(),
							ImGui::GetContentRegionAvail(),
							ImVec2(0, 1),
							ImVec2(1, 0)
						);

						viewport.destroy();

					}
					ImGui::EndChild(); 
					ImGui::End();

					gui::render();
					
					window->swap();

					deltaRenderTime = m_deltaRender.elapsed();
					m_deltaRender.restart();
				}
			}


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