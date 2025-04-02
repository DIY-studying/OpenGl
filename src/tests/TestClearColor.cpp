#include "TestClearColor.h"

#include "render.h"
#include "imgui/imgui.h"

namespace tests
{
	TestClearColor::TestClearColor()
		:m_ClearColor{1,0,0,1}
	{
	}

	TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::OnUpdate(float deltatime)
	{
	}

	void TestClearColor::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1],m_ClearColor[2],m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("color clear",m_ClearColor );
	}

}
