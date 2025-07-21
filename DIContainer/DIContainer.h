#pragma once
#include <unordered_map>
#include "IDependency.h"
#include <typeindex>
#include "Dependency_ptr.h"
#include "Pooler.h"
#include "ConstructorParam.h"
#include <functional>
#include <typeinfo>
#include "wrapper_ptr.h"

class DIContainer
{
private:
	DIContainer() = delete;
	~DIContainer() = delete;
	static std::unordered_map<std::type_index, std::function<void*(ConstructorParam& param)>*> resolver;
	static std::unordered_map<std::type_index, Pooler<IDependency*>*> poolings;
public:
	template <typename Key>
	static Wrapper_ptr<Key> GetInstance(ConstructorParam& param) requires std::is_base_of_v<IDependency, Key>
	{
		std::type_index type = std::type_index(typeid(Key));

		IDependency* instance = poolings[type]->GetInstance(param, resolver[type]);
		Dependency_ptr<Key>* ptr = new Dependency_ptr<Key>(dynamic_cast<Key*>(instance));
		Wrapper_ptr<Key> wrapper_ptr = Wrapper_ptr(ptr);

		return wrapper_ptr;
	}

	template <typename Key>
	static void ReturnInstance(Key* ptr)
	{
		std::type_index type = std::type_index(typeid(Key));
		IDependency* dependency = static_cast<IDependency*>(ptr);
		poolings[type]->ReturnInstance(dependency);
	}
	//키 값으로는 인터페이스를 받아와야 함.
	//Value의 타입은 무조건 IDependency와 Key 타입을 상속받아야함 ㅇㅋ?
	template<typename Key, typename Value> requires std::is_base_of_v<IDependency, Key> && std::is_base_of_v<Key, Value>
	static void Bind() 
	{
		std::type_index type = std::type_index(typeid(Key));
		if (resolver.contains(type))
			throw "이미 등록된 키 값입니다.";
		std::function<void* (ConstructorParam& param)>* func = new std::function<void* (ConstructorParam & param)>([](ConstructorParam& param) {return new Value(param); });
		resolver.insert({type, func});
		poolings.insert({ type, new Pooler<IDependency*>() });
	}
};

