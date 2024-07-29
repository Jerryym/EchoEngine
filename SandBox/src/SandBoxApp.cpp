#include <Echo.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace SandBoxApp {

	class ExampleLayer : public Echo::Layer
	{
	public:
		ExampleLayer()
			: Echo::Layer("Example"), m_CameraPosition(0.0f)
		{
			m_Camera.SetPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
			Draw();
		}

	public:
		virtual void OnUpdate(Echo::TimeStep ts) override
		{
			Echo::RenderCommand::SetClearColor(glm::normalize(glm::vec4(112, 128, 144, 1)));
			Echo::RenderCommand::Clear();

			Echo::Renderer::BeginScene(m_Camera);
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
			for (int y = 0; y < 20; y++)
			{
				for (int x = 0; x < 20; x++)
				{
					glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					Echo::Renderer::Submit(m_Shader, m_SquareVA, transform);
				}
			}
			Echo::Renderer::Submit(m_Shader, m_TriangleVA);
			Echo::Renderer::EndScene();
		}

		virtual void OnEvent(Echo::Event& event) override
		{
			
		}

		virtual void OnRenderUI() override
		{
			ImGui::Begin("Settings");
			ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
			ImGui::End();
		}

	private:
		void Draw()
		{
			//创建顶点数组对象
			m_TriangleVA.reset(Echo::VertexArray::CreateVertexArray());
			float triangleVertices[] = {
				-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
				 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
				 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
			};

			//创建顶点缓冲对象
			std::shared_ptr<Echo::VertexBuffer> TriangleVB;
			TriangleVB.reset(Echo::VertexBuffer::CreateBuffer(triangleVertices, sizeof(triangleVertices)));
			Echo::BufferLayout triangleLayout = {
				{ Echo::ShaderDataType::Float3, "a_Position" },
				{ Echo::ShaderDataType::Float4, "a_Color" }
			};
			TriangleVB->SetLayout(triangleLayout);
			m_TriangleVA->AddVertexBuffer(TriangleVB);

			//创建索引缓冲对象
			std::shared_ptr<Echo::IndexBuffer> TriangleIB;
			uint32_t triangleIndices[3] = { 0,1,2 };
			TriangleIB.reset(Echo::IndexBuffer::CreateBuffer(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
			m_TriangleVA->SetIndexBuffer(TriangleIB);

			//创建着色器
			std::string vertexShader = R"(
				#version 330 core
			
				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				out vec3 v_Position;
				out vec4 v_Color;

				void main()
				{
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
				}
			)";

			std::string fragmentShader = R"(
				#version 330 core
			
				layout(location = 0) out vec4 color;

				in vec3 v_Position;
				in vec4 v_Color;

				void main()
				{
					color = vec4(v_Position * 0.5 + 0.5, 1.0);
					color = v_Color;
				}
			)";
			m_Shader.reset(Echo::Shader::Create(vertexShader, fragmentShader));

			//background矩形
			m_SquareVA.reset(Echo::VertexArray::CreateVertexArray());
			float squareVertices[3 * 4] = {
				-0.75f, -0.75f, 0.0f,
				 0.75f, -0.75f, 0.0f,
				 0.75f,  0.75f, 0.0f,
				-0.75f,  0.75f, 0.0f
			};

			std::shared_ptr<Echo::VertexBuffer> SquareVB;
			SquareVB.reset(Echo::VertexBuffer::CreateBuffer(squareVertices, sizeof(squareVertices)));
			SquareVB->SetLayout({
				{ Echo::ShaderDataType::Float3, "a_Position" }
				});
			m_SquareVA->AddVertexBuffer(SquareVB);

			std::shared_ptr<Echo::IndexBuffer> SquareIB;
			uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
			SquareIB.reset(Echo::IndexBuffer::CreateBuffer(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
			m_SquareVA->SetIndexBuffer(SquareIB);

			std::string blueShaderVertexSrc = R"(
				#version 330 core
			
				layout(location = 0) in vec3 a_Position;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				out vec3 v_Position;

				void main()
				{
					v_Position = a_Position;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
				}
			)";

			std::string blueShaderFragmentSrc = R"(
				#version 330 core
			
				layout(location = 0) out vec4 color;

				in vec3 v_Position;

				void main()
				{
					color = vec4(0.2, 0.3, 0.8, 1.0);
				}
			)";
			m_BlueShader.reset(Echo::Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));
		}

	private:
		/// @brief 顶点数组对象
		std::shared_ptr<Echo::VertexArray> m_TriangleVA;
		std::shared_ptr<Echo::VertexArray> m_SquareVA;
		/// @brief 着色器
		std::shared_ptr<Echo::Shader> m_Shader;
		std::shared_ptr<Echo::Shader> m_BlueShader;

		Echo::SceneCamera m_Camera;
		glm::vec3 m_CameraPosition;

		glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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
