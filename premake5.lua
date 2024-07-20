workspace "JuceSim"
	architecture "x86_64"
	startproject "JuceDawSim"

	configurations
	{
		"Debug",
		"Release",
	}

IncludeDir = {}
IncludeDir["audioengine"] = "%{wks.location}/AudioEngine/"
IncludeDir["pluginsim"] = "%{wks.location}/PluginSim/src"
IncludeDir["lua_wrapper"] = "%{wks.location}/AudioEngine/vendor/lua_wrapper/src"
IncludeDir["lua-5.6.4"] = "%{wks.location}/AudioEngine/vendor/lua_wrapper/lua-5.6.4/src"
IncludeDir["logger"] = "%{wks.location}/Logger/src"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/lua_wrapper"
	
group ""

group "AudioEngine"
	include "AudioEngine"
group ""

group "CPlugin"
	include "CPlugin"
group ""

group "JuceDawSim"
	include "JuceDawSim"
group ""

group "JucePluginwSim"
	include "JucePluginSim"
group ""

group "Logger"
	include "Logger"
group ""

group "ThirdPartyPluginImpl"
	include "ThirdPartyPluginImpl"
group ""