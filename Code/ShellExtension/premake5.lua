project "RPFXplorer"
   kind "SharedLib"
   targetname "RPFXplorer.%{cfg.platform}"

   files { "**.h", "**.cpp", "**.c", "**.rc", "**.idl", "**.def", "**.rgs", "**.wxs" }

   includedirs { ".", "DLL/", "Resources/", "../LibRPF", "obj/%{cfg.platform}/%{cfg.buildcfg}" }

   atl('Dynamic')

   -- add /FORCE:MULTIPLE
   linkoptions { "/FORCE:MULTIPLE" }

   -- Precompiled headers
   pchheader "pch.h"
   pchsource "pch.cpp"

   links {
      "LibRPF",

      -- ATL required ones
      "kernel32.lib",
      "rpcns4.lib",
      "rpcrt4.lib",
      "oleaut32.lib",
      "uuid.lib",
      "Shell32.lib",
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

   filter "files:**.c"
      flags { "NoPCH" }