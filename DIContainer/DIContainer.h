#pragma once
#include <unordered_map>
#include "IDependency.h"
#include <typeindex>

class DIContainer
{
private:
	DIContainer() = delete;
	~DIContainer() = delete;
public:
	static std::unordered_map<std::type_index, IDependency> DIPool;
template<typename T>
static T* GetInstance()
{

}
template<typename T>
static void ReturnInstance(T* ptr)
{
	
}
};

