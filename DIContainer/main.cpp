#include <iostream>
#include "Dependency.h"
#include "TestInterface.h"

int main() 
{
	ConstructorParam param = ConstructorParam();
	Dependency_ptr<TestInterface> test = DIContainer::GetInstance<TestInterface>(param);
	test->Reset();
	test->func1();
}
