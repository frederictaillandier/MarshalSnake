#include <iostream>
#include <string>
#include "ExternalReferences.h"
#include "SharedAPI.h"
#include "Vector3.h"
#include "Logger.h"
#include "Input.h"

namespace MarshalAPI
{
	MYSHARED_API void InitCore(
		Action2<int, std::string> _action,
		Action2<int, Vector3> _setPosition,
		Action1<std::string> _log
	)
	{
		if (SharedAPI::Instance() == NULL)
			new SharedAPI(_action, _setPosition, _log);
	}

	MYSHARED_API void RunThread()
	{
		SharedAPI::Instance()->Start();
	}

	MYSHARED_API void KillThread()
	{
		if (SharedAPI::Instance() != NULL)
			SharedAPI::Instance()->KillThread();
		delete SharedAPI::Instance();
	}

	MYSHARED_API int GetGlobal()
	{
		return 0;//Use for debug purpose
	}
	
	MYSHARED_API void OnKeyUp(KeyCode k)
	{
		Input::Instance()->KeyUpReceived(k);
	}

	MYSHARED_API void OnKeyDown(KeyCode k)
	{
		Input::Instance()->KeyDownReceived(k);
	}

	MYSHARED_API void UpdateMainThread()
	{
		SharedAPI::Instance()->CollectCallStack();
	}
}