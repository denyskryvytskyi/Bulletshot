workspace "Bulletshot"
    startproject "Bulletshot"

    configurations
    {
        "Debug32",
        "Release32",
        "Debug64",
        "Release64"
    }

    filter "configurations:*32"
       architecture "x86"
 
    filter "configurations:*64"
       architecture "x64"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Bulletshot/dependencies/GLFW/include"
IncludeDir["glad"] = "%{wks.location}/Bulletshot/dependencies/glad/include"
IncludeDir["gdm"] = "%{wks.location}/Bulletshot/dependencies/gdm"
IncludeDir["ImGui"] = "%{wks.location}/Bulletshot/dependencies/imgui"

include "Bulletshot/dependencies/GLFW"
include "Bulletshot/dependencies/glad"
include "Bulletshot/dependencies/imgui"

project "Bulletshot"
    location "Bulletshot"
    kind "WindowedApp"
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
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
        "glad",
        "ImGui",
        "opengl32.lib"
    }

    defines
    {
        "GLFW_INCLUDE_NONE",
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug*"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release*"
        defines "RELEASE"
        runtime "Release"
        optimize "on"