workspace "HazelClone"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "HazelClone/vendor/GLFW/include"
IncludeDir["Glad"] = "HazelClone/vendor/Glad/include"
IncludeDir["ImGui"] = "HazelClone/vendor/imgui"
IncludeDir["Glm"] = "HazelClone/vendor/glm"

group "Dependencies"
	include "HazelClone/vendor/GLFW"
	include "HazelClone/vendor/Glad"
	include "HazelClone/vendor/imgui"
group ""

project "HazelClone"
	location "HazelClone"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "HazelClone/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.Glm}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
	}

	filter "system:windows"
		cppdialect "C++14"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "On"
		runtime "Release"

	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "On"
		runtime "Release"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"HazelClone/vendor/spdlog/include",
		"HazelClone/src",
		"%{IncludeDir.Glm}"
	}

	links
	{
		"HazelClone"
	}

	filter "system:windows"
		cppdialect "C++14"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "On"
		runtime "Release"

	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "On"
		runtime "Release"