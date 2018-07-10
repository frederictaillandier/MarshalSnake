#include "BehaviourItem.h"
#include "SharedAPI.h"

namespace MarshalAPI
{
	std::map<int, BehaviourItem*> BehaviourItem::s_itemDictionary;
	std::list<BehaviourItem*> BehaviourItem::s_toSynchronize;
	int BehaviourItem::m_UIDCounter = 0;

	void BehaviourItem::Synchronize()
	{
		SharedAPI::Instance()->CreateItem(m_UID, this);
		s_toSynchronize.remove(this);
	}

	BehaviourItem::BehaviourItem()
		: m_UID(m_UIDCounter), m_position(Vector3(0, 0, 0))
	{
		s_itemDictionary[m_UID] = this;
		s_toSynchronize.push_back(this);
		++m_UIDCounter;
	}

	BehaviourItem::~BehaviourItem()
	{
		s_itemDictionary.erase(m_UID);
	}

	void BehaviourItem::SetPosition(Vector3 const & _position)
	{
		m_position = _position;
		
		SharedAPI::Instance()->SetPosition(m_UID, _position);
	}

	void BehaviourItem::Translate(Vector3 const & _vector)
	{
		m_position += _vector;
		SharedAPI::Instance()->SetPosition(m_UID, m_position);
	}

	BehaviourItem* BehaviourItem::GetItem(int _uid)
	{
		return s_itemDictionary[_uid];
	}

	void BehaviourItem::S_Update()
	{
		while (s_toSynchronize.size() != 0)
		{
			s_toSynchronize.front()->Synchronize();
		}
		for (std::map<int, BehaviourItem*>::iterator it = s_itemDictionary.begin(); it != s_itemDictionary.end(); ++it)
		{
			it->second->Update();
		}
	}

	void BehaviourItem::Update()
	{
	
	}

	int BehaviourItem::GetUID()
	{
		return m_UID;
	}
	Vector3 BehaviourItem::GetPosition()
	{
		return m_position;
	}
}