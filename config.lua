print "Hello from Lua :)"


function getPlugins()
    return {
        "NonExistent.dll",
        "PluginSim.dll",
        "SomeOtherThatDoesNotExist.dll",
        "ThirdPartyPluginImpl.dll",
    }
end

plugins = getPlugins()

volume = 6.03