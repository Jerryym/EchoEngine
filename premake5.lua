---@diagnostic disable: undefined-global, lowercase-global
workspace "EchoEngine"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Echo/vendor/GLFW/include"
IncludeDir["Glad"] = "Echo/vendor/glad/include"
IncludeDir["ImGui"] = "Echo/vendor/imgui"
IncludeDir["glm"] = "Echo/vendor/glm"
IncludeDir["stb_image"] = "Echo/vendor/stb_image"

include "Echo/vendor/GLFW"
include "Echo/vendor/glad"
include "Echo/vendor/imgui"

project "Echo"
    location "Echo"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")   --输出目录
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")  --中间目录

    pchheader "echopch.h"
    pchsource "Echo/src/echopch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
		systemversion "latest"  --windows sdk 版本

        defines
		{
			"ECHO_PLATFORM_WINDOWS",
			"ECHO_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
		}

    filter "configurations:Debug"
        defines "ECHO_DEBUG"
        runtime "Debug"
		symbols "On"

    filter "configurations:Release"
        defines "ECHO_RELEASE"
        runtime "Release"
		optimize "On"

    filter "configurations:Dist"
        defines "ECHO_DIST"
        runtime "Release"
		optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")   --输出目录
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")  --中间目录

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Echo/vendor/spdlog/include",
        "Echo/src",
        "Echo/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Echo"
    }

    filter "system:windows"
		systemversion "latest"  --windows sdk 版本

        defines
		{
			"ECHO_PLATFORM_WINDOWS",
		}

    filter "configurations:Debug"
        defines "ECHO_DEBUG"
        runtime "Debug"
		symbols "On"

    filter "configurations:Release"
        defines "ECHO_RELEASE"
        runtime "Release"
		optimize "On"

    filter "configurations:Dist"
        defines "ECHO_DIST"
        runtime "Release"
		optimize "On"