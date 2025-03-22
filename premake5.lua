workspace "PPMRayTracer"
	configurations { "Debug", "Release" }
	platforms { "Win32","Win64" }  

project "RayTracer"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	files {
		"src/**.h",
		"src/**.cpp",
	}

	-- Set up filters in Visual Studio:
    vpaths {
        ["Header Files"] = { "src/**.h" },
        ["Source Files"] = { "src/**.cpp" },
    }

	filter ("configurations:Debug")
		defines{"DEBUG"}
		targetdir "bin/debug"

	filter ("configurations:Release")
		optimize "On"
		targetdir "bin/release"