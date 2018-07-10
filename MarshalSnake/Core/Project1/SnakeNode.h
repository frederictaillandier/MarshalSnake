#pragma once

#include "BehaviourItem.h"
#include "Vector3.h"
#include "Snake.h"

class SnakeNode : public MarshalAPI::BehaviourItem
{
	MarshalAPI::Vector3 m_target;
	bool m_stable;
	Snake const &m_snake;

public:
	SnakeNode(Snake const & _snake);
	~SnakeNode();
	
	void SetTarget(MarshalAPI::Vector3 const &v);
	MarshalAPI::Vector3 const &GetTarget() const;
	virtual std::string const GetType() const;


	void Update();
	bool IsStable() const;
};