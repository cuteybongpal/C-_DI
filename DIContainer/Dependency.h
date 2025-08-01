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
	static std::unordered_map<std::type_index, Pooler<IDependency>*> poolings;
	static bool isInitialized;
public:
	template <typename Interface>
	static Dependency_ptr<Interface> GetInstance(ConstructorParam& param) requires std::is_base_of_v<IDependency, Interface>
	{
		std::type_index type = std::type_index(typeid(Interface));

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
	//키 값으로는 인터페이스를 받아와야 함.
	//Value의 타입은 무조건 IDependency와 Key 타입을 상속std::unordered_map<std::type_index, Pooler<IDependency>*> *poolings;받아야함 ㅇㅋ?
	template<typename Interface, typename Implementation> requires std::is_base_of_v<IDependency, Interface>&& std::is_base_of_v<Interface, Implementation>
	static void Bind()
	{
		if (!isInitialized)
			poolings = std::unordered_map<std::type_index, Pooler<IDependency>*>();

		isInitialized = true;
		std::type_index type = std::type_index(typeid(Interface));
		if (poolings.contains(type))
			throw std::runtime_error("이미 등록된 키 값입니다.");

		std::function<void* (ConstructorParam&)> func = std::function<void* (ConstructorParam&)> ([](ConstructorParam& param) {return new Implementation(param); });
		Pooler<IDependency>* pooler = new Pooler<IDependency>(func);
		poolings.insert({ type, pooler});
		
		std::cout << "성공" << std::endl;
	}
};

#include "Dependency.inl"