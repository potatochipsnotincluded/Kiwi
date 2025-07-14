-- premake5.lua
workspace "Kiwi"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Sandbox"

   filter "system:windows"
      systemversion "latest"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }
      defines { "WINDOWS" }
   filter {}

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Vendor"
   include "Vendor/Glad/Build-Glad.lua"
group ""

group "Core"
   include "Kiwi-Core/Build-KiwiCore.lua"
group ""

include "Sandbox/Build-Sandbox.lua"
