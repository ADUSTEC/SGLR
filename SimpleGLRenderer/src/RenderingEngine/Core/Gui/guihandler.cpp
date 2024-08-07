#include "guihandler.h"

namespace SGLR
{

	

	void gui::init(SDL_Window* window, SDL_GLContext gl_context)
	{

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGui::StyleColorsDark();

		ImGui_ImplSDL3_InitForOpenGL(window, gl_context);
		ImGui_ImplOpenGL3_Init("#version 130");
		
	}

	void gui::destroy()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();
	}

	void gui::update()
	{
		ImGui_ImplOpenGL3_NewFrame(); 
		ImGui_ImplSDL3_NewFrame(); 
		ImGui::NewFrame(); 
	}

	void gui::render()
	{
		ImGui::Render(); 
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); 
	}

}
