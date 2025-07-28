#pragma once
#include <queue>
#include <functional>
#include "ConstructorParam.h"

template <typename T>
class Pooler
{
public: 
	std::function<void* (ConstructorParam&)> func;
	//��ü�� ������
	T* GetInstance(ConstructorParam& param)
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
	//��ü ��ȯ
	void ReturnInstance(T* instance)
	{
		poolingQueue.push(instance);
	}
	Pooler(std::function<void* (ConstructorParam&)> func) {
		poolingQueue = std::queue<T*>();
		this->func = func;
	}
private:
	std::queue<T*> poolingQueue;
};

