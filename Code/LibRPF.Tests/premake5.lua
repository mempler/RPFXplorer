project "LibRPF.Tests"
   kind "ConsoleApp"

   files { "**.h", "**.cpp", "**.c", "**.rc", "**.idl", "**.def" }

   includedirs { ".", "../LibRPF" }

   links { "LibRPF" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
