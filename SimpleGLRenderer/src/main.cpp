#include "RenderingEngine/renderengine.h"

class renderApp : public SGLR::Application
{
	public:
		renderApp() {}
		~renderApp() {}

		void onInit() override
		{}

		void onRender(float deltaTime) override
		{
			ImGui::Begin("Outliner");
			ImGui::Begin("Material Editor");
			ImGui::End();
			ImGui::End();

			ImGui::Begin("Viewport");
			ImGui::End();
			//LOG_TRACE("RENDERTIME: {}", deltaTime);
		}

		void onUpdate(float deltaTime) override
		{}

		void onTick(float deltaTime) override
		{}

	private:
};

int main(int argc, char** argv)
{
	SGLR::Log::Init(); // Initialize logger
	
	renderApp app;
	app.start();
	
	SGLR::Log::Shutdown(); // Destroy

	return 0;
}