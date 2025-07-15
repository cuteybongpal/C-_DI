#pragma once
#include <unordered_map>
#include "IDependency.h"
#include <typeindex>
#include "Dependency_ptr.h"

class DIContainer
{
private:
	DIContainer() = delete;
	~DIContainer() = delete;
public:
	static std::unordered_map<std::type_index, IDependency> DIPool;
template<typename T>
static Dependency_ptr<T> GetInstance()
{
	
}
template<typename T>
static void ReturnInstance(T* ptr)
{
	
}
};

