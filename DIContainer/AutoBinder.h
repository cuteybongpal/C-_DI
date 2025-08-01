#include "Dependency.h"

#define AUTO_RUN(Interface, Implementation)                               \
	class AutoBinder_##Implementation##__LINE__ {                         \
	public:                                                               \
		AutoBinder_##Implementation##__LINE__() {                         \
			std::cout << "Binding: " #Interface " -> " #Implementation "\n"; \
			DIContainer::Bind<Interface, Implementation>();               \
		}                                                                  \
	};                                                                     \
	static AutoBinder_##Implementation##__LINE__ global_binder_##Implementation##__LINE__;