#include "Dependency.h"
#include <unordered_map>
#include "IDependency.h"
#include <typeindex>
#include "Pooler.h"
#include <functional>


bool DIContainer::isInitialized = false;
std::unordered_map<std::type_index, Pooler<IDependency>*> DIContainer::poolings = std::unordered_map<std::type_index, Pooler<IDependency>*>();

template <typename T>
Dependency_Inner_ptr<T>* ptr = nullptr;