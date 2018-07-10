#pragma once

template<class T>
class Singleton
{
protected :
	static T* m_Instance;
public:
	Singleton();
	virtual ~Singleton();

	static T* Instance();
};

template<class T>
T* Singleton<T>::m_Instance = 0;

template<class T>
Singleton<T>::Singleton()
{
	m_Instance = static_cast <T*> (this);;
}

template<class T>
Singleton<T>::~Singleton()
{
	m_Instance = nullptr;
}

template<class T>
T* Singleton<T>::Instance()
{
	return m_Instance;
}