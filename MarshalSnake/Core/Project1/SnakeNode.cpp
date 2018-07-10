#include "SnakeNode.h"
#include "Clock.h"
#include "SharedAPI.h"

#include <string>

SnakeNode::SnakeNode(Snake const & _snake)
	: m_stable(true)
,	m_snake(_snake)
{
}

SnakeNode::~SnakeNode()
{
}

void SnakeNode::Update()
{	
	if (m_stable)
		return;	

	MarshalAPI::Vector3 &tempPos = GetPosition();
	MarshalAPI::Vector3 vectorToTarget = tempPos - m_target;
	MarshalAPI::Vector3 deltaVector = vectorToTarget * m_snake.GetSpeed() * Clock::GetDelta();

	if (vectorToTarget.Distance() > deltaVector.Distance() && vectorToTarget.Distance() > 0.1f)
	{
		tempPos += deltaVector;
	}
	else
	{	
		tempPos = m_target;
		m_stable = true;
	}
	SetPosition(tempPos);
}

bool SnakeNode::IsStable() const
{
	return m_stable;
}

void SnakeNode::SetTarget(MarshalAPI::Vector3 const &v)
{
	m_target = v;
	m_stable = false;
}

MarshalAPI::Vector3 const & SnakeNode::GetTarget() const
{
	return m_target;
}

std::string const SnakeNode::GetType() const
{
	return std::string("SnakeNode");
}
