#include <iostream>
#include "Dependency.h"
#include "TestInterface.h"

int main() 
{
	ConstructorParam param = ConstructorParam();
	DIContainer::GetInstance<TestInterface>(param);


	std::cout << "dfafda" << std::endl;
}
