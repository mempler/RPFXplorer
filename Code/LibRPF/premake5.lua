project "LibRPF"
   kind "StaticLib"

   files { "**.h", "**.cpp", "**.c", "**.rc", "**.idl", "**.def" }

   includedirs { "." }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
