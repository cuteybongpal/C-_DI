#pragma once
#include "Dependency_ptr.h"
#include "DIContainer.h"
#include "ConstructorParam.h"

template <typename T>
class Wrapper_ptr
{
public:
	void operator=(Wrapper_ptr<T>* other)
	{
		if (other == nullptr)
			ptr->operator=(nullptr);
		
		if (ptr->referenceCount == 0)
			DIContainer::ReturnInstance<T>(ptr->Tptr);

		ptr = nullptr;
	}

	T* operator->() const
	{
		return ptr->Tptr;
	}

	Wrapper_ptr<T> operator*()
	{
		ptr->SetReferenceCount(ptr->GetReferenceCount() + 1);
		return *this;
	}

	Wrapper_ptr(Dependency_ptr<T>* ptr)
	{
		this->ptr = ptr;
	}
	~Wrapper_ptr()
	{
		if (ptr == nullptr)
			return;
		ptr->SetReferenceCount(ptr->GetReferenceCount() - 1);
	}
private:
	Dependency_ptr<T>* ptr;
};

