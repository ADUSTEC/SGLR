workspace "SimpleGLRenderer"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "SimpleGLRenderer"
	location "SimpleGLRenderer"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		-- Base folder
		"%{prj.name}/resource.h",
		"%{prj.name}/SimpleGLRenderer.rc",
		"sglr.ico",
		-- Source folder
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

		-- RenderingEngine folder
		"%{prj.name}/src/RenderingEngine/**.h",
		"%{prj.name}/src/RenderingEngine/**.cpp",

		-- imgui
		"%{prj.name}/vendor/imgui/imgui.cpp",
		"%{prj.name}/vendor/imgui/imgui_draw.cpp",
		"%{prj.name}/vendor/imgui/imgui_tables.cpp",
		"%{prj.name}/vendor/imgui/imgui_widgets.cpp",
		"%{prj.name}/vendor/imgui/imgui_demo.cpp",

		"%{prj.name}/vendor/imgui/backends/imgui_impl_sdl3.cpp",
		"%{prj.name}/vendor/imgui/backends/imgui_impl_opengl3.cpp",
		
		-- stbimage
		"%{prj.name}/vendor/stbimage/stb_image.cpp"
	}

	includedirs {
		"%{prj.name}/vendor/spdlog/include",	-- SPDLOG
		"%{prj.name}/vendor/tinyxml2",			-- TINYXML2
		"%{prj.name}/vendor/glm/glm",			-- GLM
		"%{prj.name}/vendor/SDL/include",		-- SDL
		"%{prj.name}/vendor/glew/include",		-- GLEW
		"%{prj.name}/vendor/mio/include",		-- MIO
		"%{prj.name}/vendor/stbimage",		    -- STBIMAGE

		"%{prj.name}/vendor/assimp/include",	-- ASSIMP
		"%{prj.name}/vendor/assimp/BUILD/include",
		
		

		-- IMGUI
		"%{prj.name}/vendor/imgui/imconfig.h",
		"%{prj.name}/vendor/imgui/imgui.h",		
		"%{prj.name}/vendor/imgui/imgui_internal.h",
		"%{prj.name}/vendor/imgui/imstb_rectpack.h",
		"%{prj.name}/vendor/imgui/imstb_textedit.h",
		"%{prj.name}/vendor/imgui/imstb_truetype.h",

		-- IMGUIBACKENDS
		"%{prj.name}/vendor/imgui/backends/imgui_impl_opengl3.h",
		"%{prj.name}/vendor/imgui/backends/imgui_impl_sdl3.h"
	}


	libdirs {
		"%{prj.name}/vendor/glew/lib/Release/x64",		-- glew
		"%{prj.name}/vendor/SDL/BUILD/Release",		    -- SDL
		"%{prj.name}/vendor/assimp/BUILD/lib/Release",	-- assip
		"%{prj.name}/vendor/tinyxml2/BUILD/Release"		-- tinyxml2
		
	}
	
	links {
		"opengl32.lib",
		"SDL3.lib",
		"SDL3_test.lib",
		"glew32.lib",
		"tinyxml2.lib",
		"assimp-vc143-mt.lib"
	}

	postbuildcommands  {
		-- copy assets folder to build folder
		"{COPYFILE} vendor/SDL/BUILD/Release/SDL3.dll %{cfg.targetdir}/",
		"{COPYFILE} vendor/glew/bin/Release/x64/glew32.dll %{cfg.targetdir}/",
		"{COPYFILE} vendor/assimp/BUILD/bin/Release/assimp-vc143-mt.dll %{cfg.targetdir}/",
		"{COPYDIR}  assets %{cfg.targetdir}/"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
		kind "ConsoleApp"
		debugdir "%{prj.name}/assets/"

	filter "configurations:Release"
		optimize "On"
		debugdir "%{prj.name}/assets/"
		kind "WindowedApp"
		entrypoint "mainCRTStartup"

	defines {
		-- if any needed, add here.
	}