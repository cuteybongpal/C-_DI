#pragma once

template <typename T>
void Dependency_Inner_ptr<T>::operator=(Dependency_Inner_ptr<T>* null)
{
	SetReferenceCount(GetReferenceCount() - 1);
}
template <typename T>
Dependency_Inner_ptr<T>::Dependency_Inner_ptr<T>(T* ptr)
{
	Tptr = ptr;
	Dependency_Inner_ptr<T>::SetReferenceCount(1);
}
template <typename T>
void Dependency_Inner_ptr<T>::SetReferenceCount(int value) {
	referenceCount = value;
}
template <typename T>
int Dependency_Inner_ptr<T>::GetReferenceCount()
{
	return referenceCount;
}

template <typename T>
void Dependency_ptr<T>::operator=(Dependency_ptr<T>* other)
{
	if (other == nullptr)
		ptr->operator=(nullptr);

	if (ptr->referenceCount == 0)
		ReturnInstance();
	ptr = nullptr;
}
template <typename T>
T* Dependency_ptr<T>::operator->() const
{
	return ptr->Tptr;
}

template <typename T>
Dependency_ptr<T> Dependency_ptr<T>::operator*()
{
	ptr->SetReferenceCount(ptr->GetReferenceCount() + 1);
	return *this;
}
template <typename T>
Dependency_ptr<T>::Dependency_ptr(Dependency_Inner_ptr<T>* ptr)
{
	this->ptr = ptr;
}

template <typename T>
Dependency_ptr<T>::~Dependency_ptr()
{
	if (ptr == nullptr)
		return;
	ptr->SetReferenceCount(ptr->GetReferenceCount() - 1);

	if (ptr->referenceCount == 0)
		ReturnInstance();
}

template <typename T>
void Dependency_ptr<T>::ReturnInstance()
{
	 DIContainer::template ReturnInstance<T>(ptr->Tptr);
}