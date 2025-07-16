#include <unordered_map>
#include "IDependency.h"
#include <typeindex>
#include "Dependency_ptr.h"
#include "Pooler.h"
#include "DIContainer.h"

std::unordered_map<std::type_index, Pooler<IDependency>> DIContainer::DIPool = std::unordered_map<std::type_index, Pooler<IDependency>>();