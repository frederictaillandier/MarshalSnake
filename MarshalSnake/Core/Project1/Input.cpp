#include "Input.h"
#include "MainInstance.h"
#include "ActionCall.h"
#include "SharedApi.h"

namespace MarshalAPI
{
	Input::Input()
	{
		m_inputStackMutex = CreateMutex(
			NULL,              // default security attributes
			FALSE,             // initially not owned
			NULL);             // unnamed mutex

	}

	Input::~Input()
	{
		CloseHandle(m_inputStackMutex);
	}

	void Input::CollectInputStack()
	{
		size_t stackSize;

		DWORD  dwWaitResult = 0;
		dwWaitResult = WaitForSingleObject(
			m_inputStackMutex,    // handle to mutex
			INFINITE);  // no time-out interval
		if (dwWaitResult == WAIT_OBJECT_0)
		{
			stackSize = m_inputStack.size();
			ReleaseMutex(m_inputStackMutex);
		}

		for (size_t i = 0; i < stackSize; ++i)
		{
			dwWaitResult = WaitForSingleObject(
				m_inputStackMutex,    // handle to mutex
				INFINITE);  // no time-out interval
			if (dwWaitResult == WAIT_OBJECT_0)
			{
				ActionCall *ac = m_inputStack.front();
				m_inputStack.pop_front();
				ReleaseMutex(m_inputStackMutex);
				if (ac != nullptr)
				{
					(*ac)();
					delete ac;
				}
			}
		}
	}


	void Input::KeyDownReceived(KeyCode k)
	{
		DWORD  dwWaitResult;
		dwWaitResult = WaitForSingleObject(
			m_inputStackMutex,    // handle to mutex
			INFINITE);  // no time-out interval
		if (dwWaitResult == WAIT_OBJECT_0)
		{
			m_inputStack.push_back(new Action1Call<KeyCode>(&MainInstance::OnKeyDown, k));
			ReleaseMutex(m_inputStackMutex);
		}
	}

	void Input::KeyUpReceived(KeyCode k)
	{
		DWORD  dwWaitResult;
		dwWaitResult = WaitForSingleObject(
			m_inputStackMutex,    // handle to mutex
			INFINITE);  // no time-out interval
		if (dwWaitResult == WAIT_OBJECT_0)
		{
			m_inputStack.push_back(new Action1Call<KeyCode>(&MainInstance::OnKeyUp, k));
			ReleaseMutex(m_inputStackMutex);
		}

	}

	void Input::RegisterInputDownCallback(Action1<KeyCode> _callback)
	{
		m_InputDownRegistered.push_back(_callback);
	}

	void Input::RegisterInputUpCallback(Action1<KeyCode> _callback)
	{
		m_InputUpRegistered.push_back(_callback);
	}
}