#pragma once

namespace MarshalAPI
{
	class MainInstance;
	class SharedAPI;
}

#include "Singleton.h"
#include "Vector3.h"
#include "BehaviourItem.h"
#include "Keycode.h"
#include "Input.h"
#include "GameplayHolder.h"

namespace MarshalAPI
{
	class MainInstance : public Singleton<MainInstance>
	{
		SharedAPI *m_sharedAPI;
		
		GameplayHolder *m_gameplay;
	
	public:
		MainInstance(SharedAPI *_sharedAPI);
		~MainInstance();

		static void OnKeyUp(KeyCode k);
		static void OnKeyDown(KeyCode k);

		void Main();
	};
}

#include "SharedAPI.h"