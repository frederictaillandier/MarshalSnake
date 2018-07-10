#pragma once

#include <string>
#include "Vector3.h"
#include "ActionCall.h"
#include "Keycode.h"

#define MYSHARED_API __declspec(dllexport)

namespace MarshalAPI
{
	extern "C"
	{
		MYSHARED_API void InitCore(
			Action2<int, std::string> _action,
			Action2<int, Vector3> _setPosition,
			Action1<std::string> _log);
		MYSHARED_API void RunThread();
		MYSHARED_API void KillThread();
		MYSHARED_API int GetGlobal();
		MYSHARED_API void UpdateMainThread();
		MYSHARED_API void OnKeyUp(KeyCode k);
		MYSHARED_API void OnKeyDown(KeyCode k); 
	}
}