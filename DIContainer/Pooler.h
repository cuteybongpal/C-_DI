#pragma once
#include <queue>

template <typename T>
class Pooler
{
public:
	T* GetInstance();

	Pooler();
priavte:
	std::queue<T> poolingQueue;
};

