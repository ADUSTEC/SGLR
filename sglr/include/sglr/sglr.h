#pragma once
#include "core/input/keyboard.h"
#include "core/input/mouse.h"
#include "core/log/log.h"
#include "core/window/window.h"
#include "core/gui/guihandler.h"
#include "tools/clock.h"
#include "tools/readfile.h"
#include "sglr/graphics/shader.h"
#include "sglr/graphics/vertexbuffer.h"
#include "sglr/graphics/vertexarray.h"
#include "sglr/graphics/indexbuffer.h"
#include "sglr/graphics/framebuffer.h"
#include "sglr/graphics/Renderer/texture.h"
#include "sglr/graphics/Renderer/camera.h"

#include <iostream>
#include <vec2.hpp>
#include "../imgui_impl_sdl3.h"
#include "../imgui_impl_opengl3.h"
#include "../../vendor/imgui/imgui_internal.h"

// Application will be used by main by creating a custom class that inherits from Application
namespace sglr {
	class app
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
			app()
				: m_fps(0), m_ups(0), deltaUpdateTime(0), deltaRenderTime(0), deltaTickTime(0)
			{
				window = std::unique_ptr<sglrwindow>(new sglrwindow("SGLR", glm::vec2(1600, 900)));
			}

			virtual ~app() { }

			virtual void onInit() = 0; // called one time when the start function is called

			virtual void onRender(float deltaTime) = 0; // called every frame
			virtual void onTick(float deltaTime) = 0; // called for each tick
			virtual void onUpdate(float deltaTime) = 0; // called for each update

			virtual void editWindow() = 0; // ran inside of the edit window
			virtual void materialWindow() = 0; // ran inside of the edit window

			
			// return func
			 UINT getFPS() const { return m_fps; }
			 UINT getUPS() const { return m_ups; }

			 glm::vec2 getViewportSize() const { return m_viewportSize; }

			// window
			std::unique_ptr<sglrwindow> window;

		private:
			glm::vec2 m_viewportSize{};

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

				//std::unique_ptr<texture> outlinerIcon = std::make_unique<texture>("textures/sglr/t_outlinericon.png", GL_TEXTURE0);
				//std::unique_ptr<texture> materialIcon = std::make_unique<texture>("textures/sglr/t_materialicon.png", GL_TEXTURE0);
				//std::unique_ptr<texture> editIcon	  = std::make_unique<texture>("textures/sglr/t_editicon.png",     GL_TEXTURE0);
				framebuffer viewport(window->returnSize());

				// while the application is running; handle the update, tick and render functions.
				while (true)
				{
					window->update();
					keyboard::update();
					mouse::update();

					if (window->minimized())
					{
						SDL_Delay(10);
						continue;
					}
					
					gui::makeDockSpace();

					if (m_clock.elapsed() - updateTimer > updateTick)
					{
						deltaUpdateTime = m_deltaUpdate.elapsed();
						onUpdate(deltaUpdateTime);
						updates++;
						updateTimer += updateTick;
						m_deltaUpdate.restart();
					}

					ImGui::Begin("FPSCOUNTER");
					ImGui::Text("FPS: %d", m_fps);
					ImGui::End();

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
							if (ImGui::Selectable("GLB/GLTF"))	ImGui::CloseCurrentPopup();

							ImGui::EndPopup();
						}

						ImGui::Separator();

						ImGui::BeginChild("OutLinerList");

						ImGui::NewLine();
						ImGui::Indent();
						ImGui::TextDisabled("Outliner has no functionality right now :(");
					}

					ImGui::EndChild();

					ImGui::NewLine();
					ImGui::Separator();
					ImGui::Button("New Point Light");
					ImGui::SameLine();
					ImGui::Button("New Spot Light");
					ImGui::End();

					ImGui::Begin("Edit");
					editWindow();
					ImGui::End();
					
					ImGui::Begin("Material Editor");
					materialWindow();
					ImGui::End();

					ImGui::Begin("Viewport");
					{
						ImGui::BeginChild("RenderView");
						m_viewportSize = glm::vec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);

						viewport.rescale(glm::vec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));
						viewport.bind(); // bind the frame buffer

						glViewport(0, 0, (GLsizei)ImGui::GetContentRegionAvail().x, (GLsizei)ImGui::GetContentRegionAvail().y);

						glClear(GL_COLOR_BUFFER_BIT);
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
			clock m_clock{};
			clock m_deltaRender{};
			clock m_deltaUpdate{};
			clock m_deltaTick{};

			UINT m_fps = 0, m_ups = 0; // frames per sec + updates per sec variables
	};
}