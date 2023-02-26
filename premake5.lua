workspace "Echo"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Echo/vendor/GLFW/include"

include "Echo/vendor/GLFW"

project "Echo"
    location "Echo"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")   --输出目录
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")  --中间目录

    pchheader "echopch.h"
    pchsource "Echo/src/echopch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
		systemversion "latest"  --windows sdk 版本

        defines 
		{ 
			"ECHO_PLATFORM_WINDOWS",
			"ECHO_BUILD_DLL"
		}

        -- 复制dll到Sandbox.exe文件夹中
        postbuildcommands { "{COPYDIR} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox" }

    filter "configurations:Debug"
        defines "ECHO_DEBUG"
        buildoptions "/MDd"  -- 开始多线程支持调试
		symbols "On"

    filter "configurations:Release"
        defines "ECHO_RELEASE"
        buildoptions "/MD"
		symbols "On"

    filter "configurations:Dist"
        defines "ECHO_DIST"
        buildoptions "/MDd"
		symbols "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        "Echo/src"
    }

    links
    {
        "Echo"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
		systemversion "latest"  --windows sdk 版本

        defines 
		{ 
			"ECHO_PLATFORM_WINDOWS",
		}

    filter "configurations:Debug"
        defines "ECHO_DEBUG"
        buildoptions "/MDd"  -- 开始多线程支持调试
		symbols "On"

    filter "configurations:Release"
        defines "ECHO_RELEASE"
        buildoptions "/MD"
		symbols "On"

    filter "configurations:Dist"
        defines "ECHO_DIST"
        buildoptions "/MDd"
		symbols "On"