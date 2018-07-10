#include "SnakeGameplay.h"
#include "Vector3.h"
#include "BehaviourItem.h"
#include "SharedAPI.h"


MarshalAPI::GameplayHolder *InitGameplay()
{
	return new SnakeGameplay();
}

SnakeGameplay::SnakeGameplay() 
{
	m_snake = new Snake();
	m_apples.push_back(new Apple());
	m_apples.front()->Synchronize();
	m_apples.front()->SetPosition(MarshalAPI::Vector3(rand()%20-10, 0,rand() % 20 - 10));
}


SnakeGameplay::~SnakeGameplay()
{
}

void SnakeGameplay::OnKeyUp(MarshalAPI::KeyCode k)
{
}

void SnakeGameplay::OnKeyDown(MarshalAPI::KeyCode k)
{

	if (k == MarshalAPI::KeyCode::W)
	{
		m_snake->SetDirection(MarshalAPI::Vector3::FORWARD);
	}
	else if (k == MarshalAPI::KeyCode::S)
	{
		m_snake->SetDirection(MarshalAPI::Vector3::BACKWARD);
	}
	else if (k == MarshalAPI::KeyCode::A)
	{
		m_snake->SetDirection(MarshalAPI::Vector3::LEFT);
	}
	else if (k == MarshalAPI::KeyCode::D)
	{
		m_snake->SetDirection(MarshalAPI::Vector3::RIGHT);
	}
}

void SnakeGameplay::Update()
{
	m_snake->Update();
	if (m_snake->GetHead() == m_apples.front()->GetPosition())
	{
		m_snake->Grow();
		m_apples.front()->Respawn();
	}
}



