#include <unordered_map>
#include "IDependency.h"
#include <typeindex>
#include "Dependency_ptr.h"
#include "Pooler.h"
#include "DIContainer.h"
#include <functional>

std::unordered_map<std::type_index, std::function<void*(ConstructorParam& param)>*> DIContainer::resolver = std::unordered_map<std::type_index, std::function<void*(ConstructorParam& param)>*>();