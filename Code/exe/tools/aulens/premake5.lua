project "aulens"
   kind "WindowedApp"
   targetdir ( ROOT_DIR .. "/bin/%{cfg.buildcfg}/tools" )

   files { "**.h", "**.cpp" }

   includedirs { "." }

   -- Precompiled headers
   pchheader "pch.h"
   pchsource "pch.cpp"

   links {
   }
