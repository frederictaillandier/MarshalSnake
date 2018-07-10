#pragma once

#include "Vector3.h"
#include <map>
#include <list>

namespace MarshalAPI
{
	class BehaviourItem
	{
		static std::list<BehaviourItem *> s_toSynchronize;
		static std::map<int, BehaviourItem*> s_itemDictionary;
		static int m_UIDCounter;

		int m_UID;
		Vector3 m_position;

		

	public:
		BehaviourItem();
		~BehaviourItem();
		void Synchronize();

		void SetPosition(Vector3 const &_position);
		void Translate(Vector3 const &_vector);
		virtual std::string const GetType() const = 0;
		virtual void Update();


		static BehaviourItem* GetItem(int _uid);
		static void S_Update();

		int GetUID();
		Vector3 GetPosition();
	};
}