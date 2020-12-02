workspace "Bulletshot"
    architecture "x64"
    startproject "Bulletshot"

    configurations
    {
        "Debug",
        "Release",
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Tron/dependencies/GLFW/include"
IncludeDir["glad"] = "%{wks.location}/Tron/dependencies/glad/include"
IncludeDir["gdm"] = "%{wks.location}/Tron/dependencies/gdm"

include "Bulletshot/dependencies/GLFW"
include "Bulletshot/dependencies/glad"

project "Bulletshot"
    location "Bulletshot"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "bspch.h"
    pchsource "%{prj.name}/src/bspch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/dependencies/gdm/gdm/**.h",
        "%{prj.name}/dependencies/gdm/gdm/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.gdm}",
    }

    links
    {
        "GLFW",
        "glad",
        "opengl32.lib"
    }

    defines
    {
        "GLFW_INCLUDE_NONE"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "BS_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "BS_DEBUG"
        runtime "Release"
        optimize "on"