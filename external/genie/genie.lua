solution "Shadershop"
	configurations{"debug", "release"}

	location "../../vs2017"
	targetdir "../../bin"
	language "C++"
	platforms "x64"

	includedirs {"../../include"}
	includedirs {"../../external/include"}
	libdirs {"../../external/lib"}
	links { "glew32s", "SDL2", "SDL2main", "SDL2test", "openGL32"}

	project "Shadershop"
		kind "ConsoleApp"
		files { "../../include/**", "../../src/**" }
		files { "../../external/src/**"}

		defines { "GLEW_STATIC" }

		configuration "debug"
			targetsuffix "-d" 
			defines { "_CRT_SECURE_NO_WARNINGS", "WIN32","_DEBUG", "DEBUG" }
			flags { "Symbols" }

		configuration "release"
			defines { "WIN32", "NDEBUG" }
			flags { "Optimize" }
