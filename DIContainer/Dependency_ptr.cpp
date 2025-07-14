#include "Dependency_ptr.h"

template <typename T>
void Dependency_ptr<T>::SetReferenceCount(int value)
{
	referenceCount = value;
}

template <typename T>
int Dependency_ptr<T>::GetReferenceCount()
{
	return referenceCount;
}

template <typename T>
Dependency_ptr<T>& Dependency_ptr<T>::operator*() const{
	SetReferenceCount(GetReferenceCount() - 1);
	return &this;
}

template <typename T>
T* Dependency_ptr<T>::operator->() const {
	return Tptr;
}

template <typename T>
Dependency_ptr<T>& Dependency_ptr<T>::operator=(Dependency_ptr* other) {
	if (other == nullptr)
	{

	}
}