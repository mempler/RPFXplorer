project "rpf_tests"
   kind "ConsoleApp"

   files { "**.h", "**.cpp", "**.c", "**.rc", "**.idl", "**.def" }

   includedirs { ".", "../../../dll/lib/rpf" }

   links { "rpf" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
