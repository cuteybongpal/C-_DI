#pragma once
#include <iostream>
#include <typeinfo>
#include "NullObject.h"

template<typename T>
class Dependency_ptr
{
public:
	T* Tptr;
	int referenceCount;

	Dependency_ptr<T>& operator=(const Dependency_ptr<T>&) = delete;
	Dependency_ptr<T>& operator=(Dependency_ptr<T>&&) = delete;
	void operator=(Dependency_ptr<T>* null) 
	{
		std::cout << "°¨¼Ò ";
		SetReferenceCount(GetReferenceCount() - 1);
	}
	Dependency_ptr<T>(const Dependency_ptr&) = delete;
	Dependency_ptr<T>(Dependency_ptr&&) = delete;
	Dependency_ptr<T>(T* ptr)
	{
		Tptr = ptr;
		SetReferenceCount(1);
	}

	void SetReferenceCount(int value) {
		this->referenceCount = value;
		std::cout << referenceCount << std::endl;
	}

	int GetReferenceCount()
	{
		return this->referenceCount;
	}
};

