project "rpfxplr"
   kind "SharedLib"
   targetdir ( ROOT_DIR .. "/bin/%{cfg.buildcfg}/shellext" )

   files { "**.h", "**.cpp", "**.c", "**.rc", "**.idl", "**.def", "**.rgs", "**.wxs" }

   includedirs { ".", "../../lib/rpf" }

   atl('Dynamic')

   -- Precompiled headers
   pchheader "pch.h"
   pchsource "pch.cpp"

   links {
      "rpf",
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

   filter "files:**.c"
      flags { "NoPCH" }

