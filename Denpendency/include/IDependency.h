#pragma once
class IDependency
{
public:
	virtual ~IDependency() = default;
	virtual void Reset() = 0;
};

