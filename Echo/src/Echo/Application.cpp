#include "echopch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Echo/Input.h"

namespace Echo {

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Echo::ShaderDataType::Float:		return GL_FLOAT;
		case Echo::ShaderDataType::Float2:		return GL_FLOAT;
		case Echo::ShaderDataType::Float3:		return GL_FLOAT;
		case Echo::ShaderDataType::Float4:		return GL_FLOAT;
		case Echo::ShaderDataType::Mat3:		return GL_FLOAT_MAT3;
		case Echo::ShaderDataType::Mat4:		return GL_FLOAT_MAT4;
		case Echo::ShaderDataType::Int:			return GL_INT;
		case Echo::ShaderDataType::Int2:		return GL_INT;
		case Echo::ShaderDataType::Int3:		return GL_INT;
		case Echo::ShaderDataType::Int4:		return GL_INT;
		case Echo::ShaderDataType::Bool:		return GL_BOOL;
		}

		ECHO_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application::Application()
	{
		ECHO_CORE_ASSERT(s_Instance != nullptr, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT(Application::OnEvent));

		m_pImGuiLayer = new ImGuiLayer();
		PushOverlay(m_pImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.2f, 1.0f,  
			0.0f,   0.5f, 0.0f,	0.0f, 0.5f, 0.0f, 1.0f,
			0.5f,  -0.5f, 0.0f,	0.8f, 0.7f, 0.2f, 1.0f
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
		};

		m_VertexBuffer->SetLayout(layout);

		uint32_t iIndex = 0;
		layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(iIndex);
			glVertexAttribPointer(iIndex, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.m_enType), 
				element.m_bNormalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.m_nOffset);
			iIndex++;
		}

		unsigned int indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertexShader = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
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
			};
		)";

		m_Shader.reset(new Shader(vertexShader, fragmentShader));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatcher<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClose));	//控制窗口关闭

		//处理层上的事件
		for (Layer* layer : m_LayerStack)
		{
			layer->OnEvent(event);
		}
	}

	void Application::Run()
	{
		WindowResizeEvent event(1280, 720);
		
		if (event.IsInCategory(EventCategoryApplication))
		{
			ECHO_CORE_TRACE(event);
		}

		while (m_bRunning)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			
			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			// 遍历层栈，实现各层更新
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_pImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_pImGuiLayer->End();

			m_Window->OnUpdate();
		}

		if (event.IsInCategory(EventCategoryInput))
		{
			ECHO_CLIENT_TRACE(event);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& closeEvent)
	{
		m_bRunning = false;
		return true;
	}

}