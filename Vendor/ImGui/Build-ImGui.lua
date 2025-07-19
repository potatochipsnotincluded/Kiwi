project "ImGui"
   kind "StaticLib"
   language "C++"
   cppdialect "C++23"
   staticruntime "off"

   files { "Source/**.cpp", "Source/**.h" }
   
   includedirs
   {
      "Source",
	  "../GLFW/include"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
      systemversion "latest"
      links
      {
         "opengl32.lib"
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
