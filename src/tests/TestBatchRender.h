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
	class TestBatchRender :public Test
	{
	public:
		TestBatchRender();


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

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA, m_TranslationB;
	};
}

