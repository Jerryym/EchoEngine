#include "EditorLayer.h"
#include <imgui/imgui.h>

namespace Echo {

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), m_Camera(1600.f / 900.f, 1.0f)
	{
	}

	void EditorLayer::OnAttach()
	{
		m_Texture = Texture2D::CreateTexture("assets/textures/TestTexture.png");
		m_Texture2 = Texture2D::CreateTexture("assets/textures/StuccoRough.png");

		FrameBufferSpecification fboSpc;
		fboSpc.m_nWidth = Application::GetApplication().GetMainWindow().GetWidth();
		fboSpc.m_nHeight = Application::GetApplication().GetMainWindow().GetHeight();
		m_FBO = FrameBuffer::CreateFrameBuffer(fboSpc);
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(TimeStep ts)
	{
		static float rRotation = 0.0f;
		rRotation += ts * 50.0f;

		//更新相机
		m_Camera.OnUpdate(ts);

		//渲染
		Renderer2D::ResetStats();
		Renderer::Initialize();
		m_FBO->Bind();

		RenderCommand::SetClearColor(glm::vec4(169.f / 255.f, 169.f / 255.f, 169.f / 255.f, 0.4f));
		RenderCommand::Clear();

		Renderer2D::BeginScene(m_Camera);
		Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_Texture, 15.f);//background
		Renderer2D::DrawQuad({ -2.0f, 0.0f }, { 0.8f, 0.8f }, glm::vec4(127.f / 255.f, 255.f / 255.f, 212.f / 255.f, 255.f / 255.f));
		Renderer2D::DrawQuad({ 2.0f, 0.0f }, { 1.6f, 0.9f }, glm::vec4(30.f / 255.f, 144.f / 255.f, 255.f / 255.f, 255.f / 255.f));
		Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, rRotation, m_Texture2, 10.0f);
		Renderer2D::EndScene();

		Renderer2D::BeginScene(m_Camera);
		for (float y = -5.0f; y < 5.0f; y += 0.25f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.25f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Renderer2D::EndScene();
		m_FBO->UnBind();
	}

	void EditorLayer::OnRenderUI()
	{
		bool bDockingEnabled = true;
		CreateDockSpace(bDockingEnabled);

		ImGui::Begin("Settings");
		auto stats = Echo::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.m_iDrawCalls);
		ImGui::Text("Quads: %d", stats.m_iQuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
		ImGui::End();

		if (bDockingEnabled == true)
		{
			ImGui::Begin("Viewport");
			ImVec2 viewportSize = ImGui::GetContentRegionAvail();
			if (m_ViewportSize.x != viewportSize.x || m_ViewportSize.y != viewportSize.y)
			{
				m_FBO->ReSize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
				m_ViewportSize = { viewportSize.x, viewportSize.y };
			}
			uint32_t textureID = m_FBO->GetColorAttachmentRendererID();
			ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
			ImGui::End();
		}
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_Camera.OnEvent(e);
	}

	void EditorLayer::CreateDockSpace(bool bEnable)
	{
		static bool dockingEnabled = bEnable;
		if (dockingEnabled)
		{
			static bool dockspaceOpen = true;
			static bool opt_fullscreen_persistant = true;
			bool opt_fullscreen = opt_fullscreen_persistant;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
			// because it would be confusing to have two docking targets within each others.
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->Pos);
				ImGui::SetNextWindowSize(viewport->Size);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}

			// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
			// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
			// all active windows docked into it will lose their parent and become undocked.
			// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
			// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
			ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("DockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					// Disabling fullscreen would allow the window to be moved to the front of other windows, 
					// which we can't undo at the moment without finer window depth/z control.
					//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);
					if (ImGui::MenuItem("Exit"))
					{
						Echo::Application::GetApplication().Close();
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}
		}
	}

}
