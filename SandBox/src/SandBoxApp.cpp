#include <Echo.h>
#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace SandBoxApp {

	class ExampleLayer : public Echo::Layer
	{
	public:
		ExampleLayer()
			: Echo::Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
		{
			Draw();
		}

	public:
		virtual void OnUpdate(Echo::TimeStep ts) override
		{
			Echo::RenderCommand::SetClearColor(glm::normalize(glm::vec4(112, 128, 144, 1)));
			Echo::RenderCommand::Clear();

			Echo::Renderer::InitScene();
			Echo::Renderer::BeginScene(m_Camera);

			auto textureShader = m_ShaderLib.Get("Texture");
			m_Texture->Bind();
			Echo::Renderer::Submit(textureShader, m_CubeVA);
			
			Echo::Renderer::EndScene();
		}

		virtual void OnEvent(Echo::Event& event) override
		{
			
		}

		virtual void OnRenderUI() override
		{
			ImGui::Begin("Settings");
			ImGui::ColorEdit3("Cube Color", glm::value_ptr(m_CubeColor));
			ImGui::End();
		}

	private:
		void Draw()
		{
			//创建顶点数组对象
			m_CubeVA.reset(Echo::VertexArray::CreateVertexArray());
			float CubeVertices[] = {
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // 0: 左下后
				 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // 1: 右下后
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // 2: 右上后
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // 3: 左上后
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // 4: 左下前
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  // 5: 右下前
				 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // 6: 右上前
				-0.5f,  0.5f,  0.5f,  0.0f, 1.0f   // 7: 左上前
			};

			//创建顶点缓冲对象
			Echo::Ref<Echo::VertexBuffer> CubeVB;
			CubeVB.reset(Echo::VertexBuffer::CreateBuffer(CubeVertices, sizeof(CubeVertices)));
			Echo::BufferLayout CubeLayout = {
				{ Echo::ShaderDataType::Float3, "a_Position" },
				{ Echo::ShaderDataType::Float2, "a_TexCoord" }
			};
			CubeVB->SetLayout(CubeLayout);
			m_CubeVA->AddVertexBuffer(CubeVB);

			//创建索引缓冲对象
			Echo::Ref<Echo::IndexBuffer> Cube;
			uint32_t CubeIndices[] = {
				// 背面
				0, 1, 2,
				2, 3, 0,

				// 正面
				4, 5, 6,
				6, 7, 4,

				// 左面
				0, 3, 7,
				7, 4, 0,

				// 右面
				1, 5, 6,
				6, 2, 1,

				// 底面
				0, 4, 5,
				5, 1, 0,

				// 顶面
				3, 2, 6,
				6, 7, 3
			};
			Cube.reset(Echo::IndexBuffer::CreateBuffer(CubeIndices, sizeof(CubeIndices) / sizeof(uint32_t)));
			m_CubeVA->SetIndexBuffer(Cube);

			//创建着色器
			auto TexturShader = m_ShaderLib.Load("assets/shaders/Texture.glsl");
			m_Texture = Echo::Texture2D::CreateTexture("assets/textures/StuccoRoughCast.png");

			std::dynamic_pointer_cast<Echo::OpenGLShader>(TexturShader)->Bind();
			std::dynamic_pointer_cast<Echo::OpenGLShader>(TexturShader)->SetUniformInt("u_Texture", 0);
		}

	private:
		/// @brief 顶点数组对象
		Echo::Ref<Echo::VertexArray> m_CubeVA;
		/// @brief 着色器库
		Echo::ShaderLibrary m_ShaderLib;
		/// @brief 纹理贴图
		Echo::Ref<Echo::Texture2D> m_Texture;

		Echo::EditorCamera m_Camera;
		glm::vec3 m_CameraPosition;

		glm::vec3 m_CubeColor = glm::normalize(glm::vec3(0, 255, 127));
	};

	class SandBox : public Echo::Application
	{
	public:
		SandBox() 
		{
			Echo::Application::PushLayer(new ExampleLayer);
		}

		~SandBox() {}
	};

}

Echo::Application* Echo::CreateApplication()
{
	return new SandBoxApp::SandBox;
}
