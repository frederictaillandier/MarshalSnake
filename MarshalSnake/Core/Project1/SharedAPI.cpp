#include <iostream>
#include <string>
#include "SharedAPI.h"
#include "ExternalReferences.h"
#include "Logger.h"

namespace MarshalAPI
{
	DWORD WINAPI MyMain(LPVOID lpParam)
	{
		MainInstance::Instance()->Main();
		return 0;
	}

	SharedAPI::SharedAPI(Action2<int, std::string> _action,
		Action2<int, Vector3> _setPosition,
		Action1 < std::string > _log)
		: m_main(this), m_run(true)
	{
		m_CreateItem = _action;
		m_SetPosition = _setPosition;
		m_log = _log;
		m_callStackMutex = CreateMutex(
			NULL,              // default security attributes
			FALSE,             // initially not owned
			NULL);             // unnamed mutex
	}

/*	SharedAPI::SharedAPI(Action2<int, int> _action)
		: m_main(this)
	{
		m_CreateItem = _action;
	}
	*/
	void SharedAPI::Start()
	{
		hThreadHandle = CreateThread(
			NULL,                   // default security attributes
			0,                      // use default stack size
			MyMain,       // thread function name
			NULL,          // argument to thread function
			0,                      // use default creation flags
			&dwThreadId);   // returns the thread identifier		
	}

	SharedAPI::~SharedAPI()
	{
	}

	void SharedAPI::KillThread()
	{
		DWORD  dwWaitResult;
		dwWaitResult = WaitForSingleObject(
			m_callStackMutex,    // handle to mutex
			INFINITE);  // no time-out interval
		if (dwWaitResult == WAIT_OBJECT_0)
		{
			m_run = false;
			ReleaseMutex(m_callStackMutex);
		}
		DWORD rc = ::WaitForSingleObject(hThreadHandle, INFINITE);
		if (rc == WAIT_OBJECT_0) {
			CloseHandle(hThreadHandle);
			CloseHandle(m_callStackMutex);
		}
		else
		{
		}
	}

	bool SharedAPI::GetRun()
	{
		return m_run;
	}

	void SharedAPI::CollectCallStack()
	{
		size_t stackSize;
		DWORD  dwWaitResult;
		dwWaitResult = WaitForSingleObject(
			m_callStackMutex,    // handle to mutex
			INFINITE);  // no time-out interval
		if (dwWaitResult == WAIT_OBJECT_0)
		{
			stackSize = m_callStack.size();
			ReleaseMutex(m_callStackMutex);
		}
		for (size_t i = 0; i < stackSize; ++i)
		{
			dwWaitResult = WaitForSingleObject(
				m_callStackMutex,    // handle to mutex
				INFINITE);  // no time-out interval
			if (dwWaitResult == WAIT_OBJECT_0)
			{
				ActionCall *ac = m_callStack.front();
				m_callStack.pop_front();
				ReleaseMutex(m_callStackMutex);
				if (ac != nullptr)
				{
					(*ac)();
					delete ac;
				}
			}
		}
	}

	void SharedAPI::Log(std::string const _str)
	{
		Instance()->m_log(_str);
	}

	void SharedAPI::Log(char const * const _str)
	{
		Instance()->m_log(std::string(_str));
	}

	void SharedAPI::CreateItem(int UID, BehaviourItem const * const i)
	{
		DWORD  dwWaitResult;
		dwWaitResult = WaitForSingleObject(
			m_callStackMutex,    // handle to mutex
			INFINITE);  // no time-out interval
		if (dwWaitResult == WAIT_OBJECT_0)
		{
			m_callStack.push_back(new Action2Call<int, std::string>(m_CreateItem, UID, i->GetType()));
			ReleaseMutex(m_callStackMutex); 
		}
	}

	void SharedAPI::SetPosition(int UID, Vector3 _position)
	{
		DWORD  dwWaitResult;
		dwWaitResult = WaitForSingleObject(
			m_callStackMutex,    // handle to mutex
			INFINITE);  // no time-out interval
		if (dwWaitResult == WAIT_OBJECT_0)
		{
			m_callStack.push_back(new Action2Call<int, Vector3>(m_SetPosition, UID, _position));
			ReleaseMutex(m_callStackMutex);
		}
	}
}