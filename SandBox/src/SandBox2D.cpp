#include "SandBox2D.h"
#include <imgui/imgui.h>

SandBox2D::SandBox2D()
	: Echo::Layer("SandBox2D"), m_Camera(1600.f / 900.f, 1.0f)
{
}

void SandBox2D::OnAttach()
{
	m_Texture = Echo::Texture2D::CreateTexture("assets/textures/TestTexture.png");
	m_Texture2 = Echo::Texture2D::CreateTexture("assets/textures/StuccoRough.png");
}

void SandBox2D::OnDetach()
{
}

void SandBox2D::OnUpdate(Echo::TimeStep ts)
{
	static float rRotation = 0.0f;
	rRotation += ts * 50.0f;
	
	//更新相机
	m_Camera.OnUpdate(ts);

	//渲染
	Echo::Renderer2D::ResetStats();

	Echo::Renderer::Initialize();
	Echo::RenderCommand::SetClearColor(glm::vec4(169.f / 255.f, 169.f / 255.f, 169.f / 255.f, 0.4f));
	Echo::RenderCommand::Clear();

	Echo::Renderer2D::BeginScene(m_Camera);
	Echo::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_Texture, 15.f);//background
	Echo::Renderer2D::DrawQuad({ -2.0f, 0.0f }, { 0.8f, 0.8f }, glm::vec4(127.f / 255.f, 255.f / 255.f, 212.f / 255.f, 255.f / 255.f));
	Echo::Renderer2D::DrawQuad({ 2.0f, 0.0f }, { 1.6f, 0.9f }, glm::vec4(30.f / 255.f, 144.f / 255.f, 255.f / 255.f, 255.f / 255.f));
	Echo::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, rRotation, m_Texture2, 10.0f);
	Echo::Renderer2D::EndScene();

	Echo::Renderer2D::BeginScene(m_Camera);
	for (float y = -5.0f; y < 5.0f; y += 0.25f)
	{
		for (float x = -5.0f; x < 5.0f; x += 0.25f)
		{
			glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
			Echo::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
		}
	}
	Echo::Renderer2D::EndScene();
}

void SandBox2D::OnRenderUI()
{
	ImGui::Begin("Settings");

	auto stats = Echo::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.m_iDrawCalls);
	ImGui::Text("Quads: %d", stats.m_iQuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::End();
}

void SandBox2D::OnEvent(Echo::Event& e)
{
	m_Camera.OnEvent(e);
}
