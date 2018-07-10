#pragma once
#include "BehaviourItem.h"
class Apple : public MarshalAPI::BehaviourItem
{
public:
	Apple();
	~Apple();
	virtual std::string const GetType() const;
	void Respawn();
};

