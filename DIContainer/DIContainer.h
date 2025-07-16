#pragma once
#include <unordered_map>
#include "IDependency.h"
#include <typeindex>
#include "Dependency_ptr.h"
#include "Pooler.h"

class DIContainer
{
private:
	DIContainer() = delete;
	~DIContainer() = delete;
	static std::unordered_map<std::type_index, Pooler<IDependency>> DIPool;
public:
	
template<typename Key>
static Dependency_ptr<Key> GetInstance() requires requires(Key& x) { x.Reset(); }
{
	
}
template<typename T>
static void ReturnInstance(T* ptr)
{
	
}
template<typename Key, typename Value>
static void Bind()
{

}
};

