#ifndef SRC_TEST_HPP_
#define SRC_TEST_HPP_

#include <functional>
#include <vector>
#include <iostream>

namespace test{

	class Test{
	public:
		Test(){}
		virtual ~Test() {}
		virtual void onUpdate(float deltaTime){}
		virtual void onRender(){}
		virtual void onImGuiRender(){}
	};

	class TestMenu : public Test{
	public:
		TestMenu(Test*& currentTestPointer);

		void onImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name){
			std::cout << "Registering test " << name << std::endl;

			//Eclipse says that the line below has an 'invalid arguments' error, but the code seems to be compiling and working properly
			m_Tests.push_back(std::make_pair(name, [](){ return new T();} ));
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	};
}

#endif
