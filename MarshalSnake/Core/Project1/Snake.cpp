#include "Snake.h"
#include "Logger.h"

Snake::Snake() : m_snakeHead(new SnakeNode(*this))
{
	m_nodes.push_front(m_snakeHead);
	m_nodes.push_back(new SnakeNode(*this));
	m_nodes.push_back(new SnakeNode(*this));
	m_inputDirection = MarshalAPI::Vector3::ZERO;
}

Snake::~Snake()
{
	while (m_nodes.size())
	{
		delete (m_nodes.front());
		m_nodes.pop_front();
	}

}

void Snake::SetDirection(MarshalAPI::Vector3 const &direction)
{
	m_inputDirection = direction;
}

void Snake::Grow()
{
	SnakeNode *newTail = new SnakeNode(*this);
	newTail->Synchronize();
	newTail->SetTarget(m_nodes.back()->GetPosition());
	newTail->SetPosition(m_nodes.back()->GetPosition());
	m_nodes.push_back(newTail);
	m_speed *= 1.02f;
}

void Snake::Update()
{
	int i = 0;
	if (m_snakeHead->IsStable())
	{		
		std::list<SnakeNode*>::iterator it = m_nodes.end();
		std::list<SnakeNode*>::iterator it2 = it;

		--it2;//because end() is \0 we get the last one
		--it2; //then we get the pre-last one
		--it; // we sent this one to the last one
		for (it; it != m_nodes.begin(); --it) //we process from the last to the head
		{
			(*it)->SetTarget((*it2)->GetTarget());
			--it2;
		}
		m_snakeHead->SetTarget(m_snakeHead->GetTarget() + m_inputDirection);
	}
}

float Snake::GetSpeed() const
{
	return m_speed;
}

MarshalAPI::Vector3 Snake::GetHead()
{
	return m_snakeHead->GetTarget();
}
