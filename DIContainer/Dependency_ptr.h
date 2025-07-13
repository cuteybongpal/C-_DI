#pragma once
template<typename T>
class Dependency_ptr
{
public:
	T operator->() const;
	T operator*() const;
	Dependency_ptr operator=(Dependency_ptr* other);
private:
	T* Tptr;
	int referenceCount;
	void SetReferenceCount(int value);
	int GetReferenceCount();
};

