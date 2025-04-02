#pragma once

#include "test.h"

namespace tests
{
	class TestClearColor:public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltatime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_ClearColor[4];
	};
}