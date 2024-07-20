project "ThirdPartyPluginImpl"
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
	"%{IncludeDir.audioengine}"

}

libdirs {}

links
{
	"AudioEngine",
	"Logger",
	"CPlugin"
}

postbuildcommands
{
	--this should be adjusted for Linux
	"{COPYFILE} %[%{cfg.targetdir}/ThirdPartyPluginImpl.dll] %[%{wks.location}/bin/%{outputdir}/DawSim]"
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
