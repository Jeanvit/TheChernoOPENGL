#ifndef SRC_TEST_HPP_
#define SRC_TEST_HPP_

namespace test{

	class Test{
	public:
		Test(){}
		virtual ~Test() {}
		virtual void onUpdate(float deltaTime){}
		virtual void onRender(){}
		virtual void onImGuiRender(){}
	};
}

#endif
