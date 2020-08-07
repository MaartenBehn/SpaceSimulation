workspace "SpaceSimulation"
	architecture "x64"
	startproject "SpaceSimulation"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glm"] = "vendor/glm"

project "SpaceSimulation"
	location "SpaceSimulation"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "SpaceSimulation/src/pch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"SpaceSimulation/src",
		"%{IncludeDir.glm}"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"OC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "OC_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "OC_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "OC_DEBUG"
		runtime "Release"
		optimize "On"