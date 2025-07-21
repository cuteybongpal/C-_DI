#pragma once
#include <queue>
#include <functional>
#include "ConstructorParam.h"

template <typename T>
class Pooler
{
public: 
	
	//°´Ã¼¸¦ °¡Á®¿È
	T* GetInstance(ConstructorParam& param, std::function<void*(ConstructorParam&)> func)
	{
		T* instance;
		if (poolingQueue.empty())
		{
			instance = (T*)func(param);
			return instance;
		}
		instance = poolingQueue.front();
		poolingQueue.pop();
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

