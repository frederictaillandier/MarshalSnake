#pragma once
#include <list>
#include "Vector3.h"

class SnakeNode;

class Snake
{
	std::list<SnakeNode *>	m_nodes;
	SnakeNode*				m_snakeHead;
	MarshalAPI::Vector3		m_inputDirection;
	float					m_speed = 8;


public:
	Snake();
	~Snake();
	void SetDirection(MarshalAPI::Vector3 const &direction);
	void Grow();
	void Update();
	float GetSpeed() const;

	MarshalAPI::Vector3 GetHead();
};

#include "SnakeNode.h"