#include "SandboxApplication.h"

SandboxApplication::SandboxApplication() :
	m_Window("Sandbox", 1260, 720), m_Renderer(Kiwi::CreateRenderer(Kiwi::RendererType::OpenGL)) {}

SandboxApplication::~SandboxApplication() {}

bool SandboxApplication::Run()
{
	Kiwi::ShaderProgrammeCreateArgs createArgs;
	createArgs.openGLFragmentShaderPath = "../Shaders/test_triangle_frag.glsl";
	createArgs.openGLVertexShaderPath = "../Shaders/test_triangle_vert.glsl";

	Ref<Kiwi::ShaderProgramme> shaderProgramme = Kiwi::CreateShaderProgramme(createArgs);
	Ref<Kiwi::Mesh> mesh = Kiwi::LoadMesh("Assets/stall.glb");

	float metallic = 0.75f;
	float roughness = 0.3f;

	//float metallic = 0.0f;
	//float roughness = 1.0f;

	Kiwi::Material material = Kiwi::Material(Kiwi::LoadTexture("Assets/stallTexture.png", true), metallic, roughness);
	
	Kiwi::Transform transform;
	transform.rotation.y = 180;

	Kiwi::g_MainCamera->transform.position.y = 1;
	Kiwi::g_MainCamera->transform.position.z = -20;

	float rotateSpeed = 96;
	float moveSpeed = 16;
	ImVec4* colours = ImGui::GetStyle().Colors;
	colours[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colours[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colours[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colours[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colours[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
	colours[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
	colours[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
	colours[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colours[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colours[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colours[ImGuiCol_TitleBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
	colours[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colours[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
	colours[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colours[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colours[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colours[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
	colours[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colours[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colours[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colours[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colours[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colours[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colours[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colours[ImGuiCol_Header] = ImVec4(0.10f, 0.11f, 0.13f, 0.42f);
	colours[ImGuiCol_HeaderHovered] = ImVec4(0.11f, 0.12f, 0.14f, 0.43f);
	colours[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
	colours[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colours[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colours[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colours[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colours[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colours[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colours[ImGuiCol_Tab] = ImVec4(0.20f, 0.20f, 0.25f, 1.00f);
	colours[ImGuiCol_TabHovered] = ImVec4(0.20f, 0.20f, 0.25f, 1.00f);
	colours[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.25f, 0.36f);
	colours[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colours[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colours[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colours[ImGuiCol_DockingEmptyBg] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colours[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colours[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colours[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colours[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colours[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colours[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colours[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colours[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colours[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colours[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colours[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colours[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colours[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
	colours[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
	colours[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding = ImVec2(8.00f, 8.00f);
	style.FramePadding = ImVec2(5.00f, 2.00f);
	style.CellPadding = ImVec2(6.00f, 6.00f);
	style.ItemSpacing = ImVec2(6.00f, 6.00f);
	style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
	style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
	style.IndentSpacing = 25;
	style.ScrollbarSize = 15;
	style.GrabMinSize = 10;
	style.WindowBorderSize = 1;
	style.ChildBorderSize = 1;
	style.PopupBorderSize = 1;
	style.FrameBorderSize = 1;
	style.TabBorderSize = 1;
	style.WindowRounding = 7;
	style.ChildRounding = 4;
	style.FrameRounding = 3;
	style.PopupRounding = 4;
	style.ScrollbarRounding = 9;
	style.GrabRounding = 3;
	style.LogSliderDeadzone = 4;
	style.TabRounding = 4;

	ImGuiIO& io = ImGui::GetIO();
	ImFont* normal = io.Fonts->AddFontFromFileTTF("Assets/fonts/Roboto-Regular.ttf", 13.85f);
	ImFont* bold = io.Fonts->AddFontFromFileTTF("Assets/fonts/Roboto-Bold.ttf", 13.85f);

	ImGui::LoadIniSettingsFromDisk(io.IniFilename);

	ImVec2 prevSize = ImVec2(0, 0);

	bool resized = false;

	while (!m_Window.ShouldClose())
	{
		m_Window.FrameBegin();

		//transform.rotation.y += 64.0f*m_Window.GetDeltaTime();
		
		if (Kiwi::Input::GetKeyDown(ImGuiKey_A))
			Kiwi::g_MainCamera->transform.rotation.y += rotateSpeed * m_Window.GetDeltaTime();
		if (Kiwi::Input::GetKeyDown(ImGuiKey_D))
			Kiwi::g_MainCamera->transform.rotation.y -= rotateSpeed * m_Window.GetDeltaTime();

		glm::vec3 forward = Kiwi::GetForwardVector(Kiwi::g_MainCamera->transform);

		if (Kiwi::Input::GetKeyDown(ImGuiKey_W))
			Kiwi::g_MainCamera->transform.position += (forward * moveSpeed) * (float)m_Window.GetDeltaTime();
		if (Kiwi::Input::GetKeyDown(ImGuiKey_S))
			Kiwi::g_MainCamera->transform.position -= (forward * moveSpeed) * (float)m_Window.GetDeltaTime();

		if (Kiwi::Input::GetKeyDown(ImGuiKey_Q))
			Kiwi::g_MainCamera->transform.position.y += moveSpeed * m_Window.GetDeltaTime();
		if (Kiwi::Input::GetKeyDown(ImGuiKey_E))
			Kiwi::g_MainCamera->transform.position.y -= moveSpeed * m_Window.GetDeltaTime();

		m_Renderer->Clear(glm::vec4(0.00f, 0.00f, 0.00f, 1.00f)); 

		m_Renderer->PushMesh(mesh, shaderProgramme, transform, material);

		m_Renderer->Render();

		m_Renderer->ImGuiStartFrame();

		ImGui::DockSpaceOverViewport(ImGui::GetWindowDockID(), ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

		static bool openRestartPopup = false;

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Reset Material"))
				{
					material.metallic = 0.75f;
					material.roughness = 0.3f;
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Editor"))
			{
				if (ImGui::MenuItem("Reset INI"))
				{
					std::filesystem::path source = "Assets/default.ini";
					std::filesystem::path destination = "imgui.ini";

					std::ifstream srcStream(source);
					std::ofstream dstStream(destination);

					KW_ASSERT("Cannot open file", srcStream.is_open() && dstStream.is_open());

					dstStream << srcStream.rdbuf();

					openRestartPopup = true;
				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		if (openRestartPopup)
		{
			ImGui::OpenPopup("RestartPopup");
			openRestartPopup = false;
		}

		if (ImGui::BeginPopup("RestartPopup"))
		{
			ImGui::PushFont(bold);
			ImGui::Text("You must restart for the changes to take effect.");
			ImGui::PopFont();

			if (ImGui::Button("Ok"))
			{
				ImGui::CloseCurrentPopup();

				ImGui::EndPopup();

				m_Renderer->ImGuiEndFrame();
				m_Renderer->ImGuiShutdown();

				m_Window.~Window();

				return false; 
			}
			ImGui::EndPopup();
		}

		m_Renderer->DrawImGuiViewport();

		ImGui::Begin("Material");

		ImGui::Text("Metallic: ");
		ImGui::SameLine();
		ImGui::DragFloat("###metallicobj", &material.metallic, 0.025f, 0, 1);

		ImGui::Text("Roughness: ");
		ImGui::SameLine();
		ImGui::DragFloat("###roughnessobj", &material.roughness, 0.025f, 0, 1);

		ImGui::End();
		
		ImGui::Begin("Statistics");

		ImGui::Text("Ms/f: %.01f", m_Window.GetDeltaTime() * 1000);

		glm::vec2 mousePos = Kiwi::Input::GetMousePosition();
		ImGui::Text("Mouse Position: X %.1f Y %.1f", mousePos.x, mousePos.y);

		ImGui::End();

		m_Renderer->ImGuiEndFrame();

		m_Window.Present();
	}

	return true;
}
