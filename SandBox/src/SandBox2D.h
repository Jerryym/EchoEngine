#pragma once
#include <Echo.h>

class SandBox2D : public Echo::Layer
{
public:
	SandBox2D();
	virtual ~SandBox2D() {}

public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Echo::TimeStep ts) override;
	virtual void OnRenderUI() override;
	virtual void OnEvent(Echo::Event& e) override;

private:
	/// @brief 顶点数组对象
	Echo::Ref<Echo::VertexArray> m_CubeVA;
	/// @brief 着色器库
	Echo::ShaderLibrary m_ShaderLib;
	/// @brief 纹理贴图
	Echo::Ref<Echo::Texture2D> m_Texture;
	/// @brief 编辑器相机
	Echo::EditorCamera m_Camera;
};

