project "Kiwi-Core"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp", "Source/**.inl" }
   
   includedirs
   {
      "Source",
	  "../Vendor/GLFW/include",
	  "../Vendor/Glad/include",
	  "../Vendor/glm/include",
	  "../Vendor/Assimp/include",
	  	"../Vendor/stb_image"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
   
   links
   {
      "Glad"
   }
   
   filter "system:windows"
      systemversion "latest"
      links
      {
	     "../Vendor/GLFW/glfw3.lib",
		 "../Vendor/GLFW/glfw3_mt.lib",
		 "../Vendor/Assimp/lib/assimp-vc143-mt.lib",
         "shlwapi.lib",
         "user32.lib",
         "gdi32.lib",
         "shell32.lib",
         "advapi32.lib",
         "ws2_32.lib",
         "winmm.lib",
         "setupapi.lib",
         "version.lib",
         "imm32.lib",
         "cfgmgr32.lib"
      }

   filter "configurations:Debug"
      defines { "DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist"
      defines { "DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"
