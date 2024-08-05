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
			LOG_TRACE("RENDERTIME: {}", deltaTime);
		}

		void onUpdate(float deltaTime) override
		{
			LOG_TRACE("UPDATETIME: {}", deltaTime);
		}

		void onTick(float deltaTime) override
		{
			LOG_TRACE("TICKTIME: {}", deltaTime);
		}

	private:
};

int main(int argc, char** argv)
{
	SGLR::Log::Init(); // Initialize logger
	
	renderApp app;
	app.start();
	
	SGLR::Log::Shutdown(); // Destroy
}