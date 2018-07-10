#pragma once
#include "Singleton.h"
#include <windows.h>
#include <list>
#include "ExternalReferences.h"
#include "Keycode.h"

namespace MarshalAPI
{
	class Input : public Singleton<Input>
	{
		HANDLE m_inputStackMutex;
		std::list<ActionCall*> m_inputStack;

		std::list<Action1<KeyCode>> m_InputDownRegistered;
		std::list<Action1<KeyCode>> m_InputUpRegistered;
	public:
		Input();
		~Input();

		void RegisterInputDownCallback(Action1<KeyCode> _callback);
		void RegisterInputUpCallback(Action1<KeyCode> _callback);

		void CollectInputStack();

		void KeyDownReceived(KeyCode k);
		void KeyUpReceived(KeyCode k);

	};
}