#pragma once
#include "AutoBinder.h"
#include "IDependency.h"
#include "ConstructorParam.h"

class TestInterface : public IDependency
{
public:
	virtual ~TestInterface() = default;
	virtual void Reset() = 0;
};

class TestImplementation : public TestInterface
{
public:
	void Reset() override {
		;
	}
	TestImplementation(ConstructorParam& param) {
		;
	}
};

AUTO_RUN(TestInterface, TestImplementation);