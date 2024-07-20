project "DawSim"
kind "ConsoleApp"
language "C++"
cppdialect "C++20"
--staticruntime "off"

targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
debugdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")


files
{
	"src/**.h",
	"src/**.cpp",
}

defines
{
}

includedirs
{
	"src",
	"%{IncludeDir.audioengine}",
	"%{IncludeDir.pluginsim}",
	"%{IncludeDir.logger}",
	"%{IncludeDir.lua_wrapper}"
}

libdirs {}

links
{
	"AudioEngine",
	"Logger"
}


filter "system:windows"
systemversion "latest"

defines
{
}

links
{
}

filter "configurations:Debug"
defines "PUL_DEBUG"
runtime "Debug"
symbols "on"

links
{
}

filter "configurations:Release"
defines "PUL_RELEASE"
runtime "Release"
optimize "on"

links
{
}

filter "configurations:Dist"
defines "PUL_DIST"
runtime "Release"
optimize "on"

links
{
}
