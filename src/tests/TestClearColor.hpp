#ifndef SRC_TESTCLEARCOLOR_HPP_
#define SRC_TESTCLEARCOLOR_HPP_

#include "Test.hpp"

namespace test{
	class TestClearColor : public Test {
	public:
		TestClearColor();
		~TestClearColor();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
		float m_ClearColor[4];
	};
}

#endif
