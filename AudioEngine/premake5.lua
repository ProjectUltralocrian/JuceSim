project "AudioEngine"
kind "SharedLib"
language "C++"
cppdialect "C++20"
--staticruntime "off"

targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

files
{
	"src/**.h",
	"src/**.cpp",
	"./vendor/lua_wrapper/src/**.cpp",
	"./vendor/lua_wrapper/src/**.h"
}

defines
{
	"PUL_DLL_BUILD",
}

includedirs
{
	".",
	"src",
	"%{IncludeDir.logger}",
	"%{IncludeDir.lua_wrapper}",
}

libdirs { "%{prj.location}" }

links
{
	"Logger", --"lua54"
}

postbuildcommands
{
	"{COPYFILE} %[%{wks.location}/config.lua] %[%{wks.location}/bin/%{outputdir}/DawSim]",

	--this should be adjusted for Linux
	"{COPYFILE} %[%{cfg.targetdir}/AudioEngine.dll] %[%{wks.location}/bin/%{outputdir}/DawSim]",
	
	--this should be adjusted for Linux
	"{COPYFILE} %[%{wks.location}/AudioEngine/vendor/lua_wrapper/lua-5.4.6/lua54.dll] %[%{wks.location}/bin/%{outputdir}/DawSim]"
}


filter "system:windows"
systemversion "latest"

defines
{
}

links
{
	--this should be adjusted for Linux
	"liblua54"
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
