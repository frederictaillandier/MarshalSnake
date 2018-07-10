#pragma once

namespace MarshalAPI
{
	class SharedAPI;
}
#include <windows.h>
#include <list>
#include <functional>
#include <string>
#include "Singleton.h"
#include "ExternalReferences.h"
#include "MainInstance.h"
#include "Input.h"
#include "Clock.h"
#include "Logger.h"

namespace MarshalAPI
{
	class SharedAPI : public Singleton<SharedAPI>
	{
		DWORD   dwThreadId;
		HANDLE  hThreadHandle;
		HANDLE m_callStackMutex;
		Action2<int, std::string> m_CreateItem;
		Action2<int, Vector3> m_SetPosition;
		Action1<std::string> m_log;

		MainInstance m_main;
		Input m_input;
		Clock m_clock;
		bool m_run;
		std::list<ActionCall*> m_callStack;
		Logger m_logger;
	public:
//		SharedAPI::SharedAPI(Action2<int, int> _action);
		SharedAPI(Action2<int, std::string> _action,
			Action2<int, Vector3> _setPosition,
			Action1<std::string> _log);
		~SharedAPI();

		void Start();

		void CreateItem(int UID, BehaviourItem const * const i);
		void SetPosition(int UID, Vector3 _position);
		static void Log(std::string const  _str);
		static void Log(char const * const _str);

		void CollectCallStack();
		void KillThread();
		bool GetRun();
	};
}