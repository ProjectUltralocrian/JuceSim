project "CPlugin"
kind "StaticLib"
language "C"
--cppdialect "C17"
--staticruntime "off"

targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

--pchheader "hzpch.h"
--pchsource "src/hzpch.cpp"

files
{
	"./**.h",
	"./**.c",
}

defines
{
	--"PUL_DLL_BUILD",
}

includedirs
{
	"src",
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
