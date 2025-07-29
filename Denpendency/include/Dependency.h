#pragma once
#include <iostream>
#include <typeinfo>
#include "ConstructorParam.h"
#include <unordered_map>
#include "IDependency.h"
#include <typeindex>
#include "Pooler.h"
#include <functional>

template<typename T>
class Dependency_Inner_ptr
{
public:
	T* Tptr;
	int referenceCount;

	Dependency_Inner_ptr<T>& operator=(const Dependency_Inner_ptr<T>&) = delete;
	Dependency_Inner_ptr<T>& operator=(Dependency_Inner_ptr<T>&&) = delete;
	void operator=(Dependency_Inner_ptr<T>* null);

	Dependency_Inner_ptr<T>(const Dependency_Inner_ptr<T>&) = delete;
	Dependency_Inner_ptr<T>(Dependency_Inner_ptr<T>&&) = delete;
	Dependency_Inner_ptr<T>(T* ptr);

	void SetReferenceCount(int value);

	int GetReferenceCount();
};

template <typename T>
class Dependency_ptr
{
public:
	void operator=(Dependency_ptr<T>* other);

	T* operator->() const;

	Dependency_ptr<T> operator*();

	Dependency_ptr(Dependency_Inner_ptr<T>* ptr);
	~Dependency_ptr();
	void ReturnInstance();
private:
	Dependency_Inner_ptr<T>* ptr;
};
class DIContainer
{
private:
	DIContainer() = delete;
	~DIContainer() = delete;
	static std::unordered_map<std::type_index, Pooler<IDependency*>*> poolings;
public:
	template <typename Interface>
	static Dependency_ptr<Interface> GetInstance(ConstructorParam& param) requires std::is_base_of_v<IDependency, Interface>
	{
		std::type_index type = std::type_index(typeid(Key));

		IDependency* instance = poolings[type]->GetInstance(param);
		Dependency_Inner_ptr<Interface>* inner_ptr = new Dependency_Inner_ptr<Interface>(dynamic_cast<Interface*>(instance));
		Dependency_ptr<Interface> dependency_ptr = Dependency_ptr<Interface>(inner_ptr);

		return dependency_ptr;
	}

	template <typename Interface>
	static void ReturnInstance(Interface* ptr) requires std::is_base_of_v<IDependency, Interface>
	{
		std::type_index type = std::type_index(typeid(Interface));
		IDependency* dependency = static_cast<IDependency*>(ptr);
		poolings[type]->ReturnInstance(dependency);
	}
	//Ű �����δ� �������̽��� �޾ƿ;� ��.
	//Value�� Ÿ���� ������ IDependency�� Key Ÿ���� ��ӹ޾ƾ��� ����?
	template<typename Interface, typename Implementation> requires std::is_base_of_v<IDependency, Interface>&& std::is_base_of_v<Interface, Implementation>
	static void Bind()
	{
		std::type_index type = std::type_index(typeid(Key));
		if (poolings.contains(type))
			throw std::runtime_error("�̹� ��ϵ� Ű ���Դϴ�.");
		std::function<void* (ConstructorParam& param)>* func = new std::function<void* (ConstructorParam & param)>([](ConstructorParam& param) {return new Implementation(param); });
		poolings.insert({ type, new Pooler<IDependency*>(func) });
	}
};

#include "Dependency.inl"