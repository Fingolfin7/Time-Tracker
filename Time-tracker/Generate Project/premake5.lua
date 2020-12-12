-- premake5.lua
workspace "Time-tracker"
	location "../"
	configurations {"Debug", "Release"}

project "Plane2D"
	architecture "x86"

	location "../Time-tracker"
	kind "ConsoleApp"
	language "C++"

	targetdir "../%{cfg.buildcfg}"
	files {"../Time-tracker/**.cpp"}

filter "configurations:Debug"
	defines {"DEBUG"}
	symbols "On"

filter "configurations:Release"
	defines {"NDEBUG"}
	optimize "On"
