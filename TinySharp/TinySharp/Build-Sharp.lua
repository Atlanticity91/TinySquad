include "../Sharp-Extension.lua"

project "TinySharp"
    language "C#"
    kind "SharedLib"
    dotnetframework "net8.0"
    clr "Unsafe"
    architecture "universal"

    targetdir ("%{wks.location}/bin/")
    objdir ("%{wks.location}/bin-int/%{prj.name}")

    files { "**.cs" }
    
    propertytags {
        { "Nullable", "enable" },
        { "ImplicitGlobalUsings", "true" },
        { "AppendRuntimeIdentifierToOutputPath", "false" },
        { "UseCommonOutputDirectory", "true" },
        { "IntermediateOutputPath", "../../bin-int/" },
    }

    disablewarnings { "CS8500" }
