#pragma once

template<typename T>
class Dependency_ptr
{
public:
	T* operator->() const
	{
		return Tptr;
	}
	Dependency_ptr<T>* operator*() const
	{
		SetReferenceCount(GetReferenceCount() + 1);
		return this;
	}
	void operator=(std::nullptr_t n)
	{
		SetReferenceCount(GetReferenceCount() - 1);
	}
	Dependency_ptr<T>(T* ptr) 
	{
		Tptr = ptr;
		referenceCount = 1;
	}
private:
	T* Tptr;
	int referenceCount;
	void SetReferenceCount(int value) {
		referenceCount = value;
		if (referenceCount <= 0)
		{
			;
			//todo : DIContainer¿¡ °´Ã¼ ¹ÝÈ¯
		}
	}
	int GetReferenceCount() 
	{
		return referenceCount;
	}
};

