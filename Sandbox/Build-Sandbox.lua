project "Sandbox"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source",

      -- Include Core
      "../Kiwi-Core/Source",
      "../Vendor/GLFW/include",
      "../Vendor/Glad/include",
	  "../Vendor/glm/include",
	 "../Vendor/Assimp/include",
	 "../Vendor/stb_image"
   }

   links { "Kiwi-Core" }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
   	  includedirs { os.getenv("VULKAN_SDK") .. "/Include" }
      systemversion "latest"

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
