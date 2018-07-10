#pragma once

#include "Keycode.h"


namespace MarshalAPI
{
	class GameplayHolder
	{
	public:
		GameplayHolder();
		~GameplayHolder();

		virtual void OnKeyUp(KeyCode k) = 0;
		virtual void OnKeyDown(KeyCode k) = 0;
		virtual void Update() = 0;
	};
}