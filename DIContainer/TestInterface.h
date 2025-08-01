#pragma once
#include "AutoBinder.h"
#include "IDependency.h"
#include "ConstructorParam.h"
#include <iostream>

class TestInterface : public IDependency
{
public:
	virtual ~TestInterface() = default;
	virtual void Reset() = 0;
	virtual void func1() = 0;
};

class TestImplementation : public TestInterface
{
public:
	void Reset() override {
		std::cout << "초기화" << std::endl;
	}
	void func1() override {
		std::cout << "기능 1" << std::endl;
	}
	TestImplementation(ConstructorParam& param) {
		;
	}
};