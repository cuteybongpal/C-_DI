#pragma once
template<typename T>
class Dependency_ptr
{
public:
	T* operator->() const;
	Dependency_ptr<T>& operator*() const;
	Dependency_ptr<T>& operator=(Dependency_ptr<T>* other);
	bool operator==(Dependency_ptr<T>* other1, other2) const;
private:
	T* Tptr;
	int referenceCount;
	void SetReferenceCount(int value);
	int GetReferenceCount();
};

