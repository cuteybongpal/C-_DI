#include <unordered_map>
#include "../include/IDependency.h"
#include "../include/Dependency.h"
#include <typeindex>
#include "../include/Pooler.h"
#include <functional>

std::unordered_map<std::type_index, Pooler<IDependency*>*> DIContainer::poolings = std::unordered_map<std::type_index, Pooler<IDependency*>*>();