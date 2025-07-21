#include <iostream>
#include "Dependency_ptr.h"
#include "NullObject.h"
#include "wrapper_ptr.h"

int main() 
{
	Wrapper_ptr<int> int_ptr = Wrapper_ptr<int>(new Dependency_ptr<int>(new int(5)));
	

	Wrapper_ptr<int> int_ptr1 = *int_ptr;

	int_ptr1 = nullptr;
	int_ptr = nullptr;
}
