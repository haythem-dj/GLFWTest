project "GLFWTest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/**.h",
		"src/**.cpp"
	}

	defines
	{
		"GLEW_STATIC"
	}

	includedirs
	{
		"%{wks.location}/%{prj.name}/include",
		"%{wks.location}/%{prj.name}/vendor/GLFW/include",
		"%{wks.location}/%{prj.name}/vendor/GLEW/include",
		"%{wks.location}/%{prj.name}/vendor/GLM/include",
		"%{wks.location}/%{prj.name}/vendor/STB/include"
	}

	libdirs
	{
		"%{wks.location}/%{prj.name}/vendor/GLFW/lib",
		"%{wks.location}/%{prj.name}/vendor/GLEW/lib",
	}

	links
	{
		"glfw3.lib",
		"glew32s.lib",
		"opengl32.lib"
	}

	filter "configurations:Debug"
			defines "DEBUG"
			runtime "Debug"
			symbols "on"

	filter "configurations:Release"
			defines "NDEBUG"
			runtime "Release"
			optimize "on"