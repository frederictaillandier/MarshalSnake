#pragma once
#include <list>
#include "GameplayHolder.h"
#include "Vector3.h"
#include "BehaviourItem.h"
#include "SnakeNode.h"
#include "Snake.h"
#include "Apple.h"

class SnakeGameplay : public MarshalAPI::GameplayHolder
{
	MarshalAPI::BehaviourItem*	m_map[20][20];
	Snake*						m_snake;
	std::list<Apple *>	        m_apples;

public:
	SnakeGameplay();
	~SnakeGameplay();

	void OnKeyUp(MarshalAPI::KeyCode k) override;
	void OnKeyDown(MarshalAPI::KeyCode k) override;
	void Update() override;
};
