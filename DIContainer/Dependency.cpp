#include "Dependency.h"
#include <unordered_map>
#include "IDependency.h"
#include <typeindex>
#include "Pooler.h"
#include <functional>

std::unordered_map<std::type_index, Pooler<IDependency*>*> DIContainer::poolings = std::unordered_map<std::type_index, Pooler<IDependency*>*>();