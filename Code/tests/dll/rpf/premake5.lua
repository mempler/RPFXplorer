project "rpf_tests"
   kind "ConsoleApp"

   files { "**.h", "**.cpp", "**.c", "**.rc", "**.idl", "**.def" }

   includedirs { ".", "../../../dll/lib/rpf" }

   links { "rpf" }

   pchheader "pch.h"
   pchsource "pch.cpp"

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
