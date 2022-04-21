project "rpf"
   kind "SharedLib"

   files { "**.h", "**.cpp", "**.c", "**.rc", "**.idl", "**.def" }

   includedirs { "." }

   defines { "__RPF" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
