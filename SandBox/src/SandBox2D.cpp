#include "SandBox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

SandBox2D::SandBox2D()
	: Echo::Layer("SandBox2D"), m_Camera(1600.f / 900.f, 1.0f)
{
}

void SandBox2D::OnAttach()
{
	m_Texture = Echo::Texture2D::CreateTexture("assets/textures/TestTexture.png");
}

void SandBox2D::OnDetach()
{
}

void SandBox2D::OnUpdate(Echo::TimeStep ts)
{
	//更新相机
	m_Camera.OnUpdate(ts);

	//渲染
	Echo::Renderer::Initialize();
	Echo::RenderCommand::SetClearColor(glm::normalize(glm::vec4(112, 128, 144, 1)));
	Echo::RenderCommand::Clear();

	Echo::Renderer2D::BeginScene(m_Camera);
	Echo::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::normalize(glm::vec4(127, 255, 212, 1)));
	Echo::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, glm::normalize(glm::vec4(30, 144, 255, 1)));
	Echo::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture);
	Echo::Renderer2D::EndScene();
}

void SandBox2D::OnRenderUI()
{
}

void SandBox2D::OnEvent(Echo::Event& e)
{
	m_Camera.OnEvent(e);
}
