#pragma once

class NullObject;

template<typename T>
class Dependency_ptr
{
public:
	T* operator->() const;
	Dependency_ptr<T>* operator*() const;
	void operator=(std::nullptr_t n);
private:
	T* Tptr;
	int referenceCount;
	void SetReferenceCount(int value);
	int GetReferenceCount();
};

