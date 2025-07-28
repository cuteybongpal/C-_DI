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
	template <typename Key>
	static Dependency_ptr<Key> GetInstance(ConstructorParam& param) requires std::is_base_of_v<IDependency, Key>
	{
		std::type_index type = std::type_index(typeid(Key));

		IDependency* instance = poolings[type]->GetInstance(param);
		Dependency_Inner_ptr<Key>* inner_ptr = new Dependency_Inner_ptr<Key>(dynamic_cast<Key*>(instance));
		Dependency_ptr<Key> dependency_ptr = Dependency_ptr<Key>(inner_ptr);

		return dependency_ptr;
	}

	template <typename Key>
	static void ReturnInstance(Key* ptr) requires std::is_base_of_v<IDependency, Key>
	{
		std::type_index type = std::type_index(typeid(Key));
		IDependency* dependency = static_cast<IDependency*>(ptr);
		poolings[type]->ReturnInstance(dependency);
	}
	//키 값으로는 인터페이스를 받아와야 함.
	//Value의 타입은 무조건 IDependency와 Key 타입을 상속받아야함 ㅇㅋ?
	template<typename Key, typename Value> requires std::is_base_of_v<IDependency, Key>&& std::is_base_of_v<Key, Value>
	static void Bind()
	{
		std::type_index type = std::type_index(typeid(Key));
		if (poolings.contains(type))
			throw "이미 등록된 키 값입니다.";
		std::function<void* (ConstructorParam& param)>* func = new std::function<void* (ConstructorParam & param)>([](ConstructorParam& param) {return new Value(param); });
		poolings.insert({ type, new Pooler<IDependency*>(func) });
	}
};

#include "Dependency.inl"