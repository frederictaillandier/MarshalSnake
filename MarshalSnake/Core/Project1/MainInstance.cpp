
#include "MainInstance.h"
#include "SharedAPI.h"
#include "BehaviourItem.h"
#include "Keycode.h"
#include "Clock.h"


using namespace MarshalAPI;

MarshalAPI::GameplayHolder *InitGameplay();

MainInstance::MainInstance(MarshalAPI::SharedAPI *_sharedAPI)
	: m_sharedAPI(_sharedAPI)
{
}


MainInstance::~MainInstance()
{
	
}

void MainInstance::OnKeyUp(MarshalAPI::KeyCode k)
{
	if (Instance() && Instance()->m_gameplay != nullptr)
		Instance()->m_gameplay->OnKeyUp(k);
}

void MainInstance::OnKeyDown(MarshalAPI::KeyCode k)
{
	if (Instance() && Instance()->m_gameplay != nullptr)
		Instance()->m_gameplay->OnKeyDown(k);
}

void MainInstance::Main()
{
	m_gameplay = InitGameplay();
	
	while (SharedAPI::Instance()->GetRun())
	{
		MarshalAPI::Input::Instance()->CollectInputStack();
		Clock::Update();
		BehaviourItem::S_Update();
		if (m_gameplay != nullptr)
			m_gameplay->Update();
	}
}
