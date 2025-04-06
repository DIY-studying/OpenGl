#pragma once
#include "Test.h"
#include "memory"
#include "imgui/imgui.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Render.h"
#include "Texture.h"

namespace tests
{
	struct Vec2
	{
		float x, y;
	};
	struct Vertex
	{
		Vec2 position;
		Vec2 texcoord;
		float texID;
	};
	class TestDynamicBuffer :public Test
	{
	public:
		TestDynamicBuffer();


		virtual void OnUpdate(float deltatime);
		virtual void OnRender();
		virtual void OnImGuiRender();
	private:
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<IndeiceBufer> m_IndeiceBufer;
		std::unique_ptr<Texture> m_TextureA;
		std::unique_ptr<Texture> m_TextureB;

		Vec2 posA, posB;
	};
}