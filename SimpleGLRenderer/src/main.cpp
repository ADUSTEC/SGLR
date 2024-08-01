#include <iostream>
#include <string>
#include <GL/glew.h>
#include "RenderingEngine/RenderEngine.h"
#include <assimp/Importer.hpp>

int main(int argc, char** argv)
{
	SGLR::Log::Init(); // Initialize logger
	
	// testing
	LOG_TRACE("This is a log message");
	LOG_INFO("This is an info message");
	LOG_DEBUG("This is a debug message");
	LOG_ERROR("This is an error message");

	system("PAUSE");

	SGLR::Log::Shutdown(); // Destroy
}