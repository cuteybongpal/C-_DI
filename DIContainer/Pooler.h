#pragma once
#include <queue>
#include "ConstructorParam.h"

template <typename T>
class Pooler
{
public:
	//°´Ã¼¸¦ °¡Á®¿È
	T* GetInstance(ConstructorParam& param) 
	{
		if (poolingQueue.size() <= 0)
			return new T(param);
		
		T* instance = poolingQueue.pop();
		return instance;
	}
	//°´Ã¼ ¹ÝÈ¯
	void ReturnInstance(T* instance)
	{
		poolingQueue.push(instance);
	}
	Pooler() {
		poolingQueue = std::queue<T*>();
	}
private:
	std::queue<T*> poolingQueue;
};

