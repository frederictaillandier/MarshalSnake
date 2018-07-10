#pragma once

namespace MarshalAPI
{
	using Action0 = void(*)();
	template<typename T>
	using Action1 = void(*)(T);
	template<typename T1, typename T2>
	using Action2 = void(*)(T1, T2);
	template<typename T1, typename T2, typename T3>
	using Action3 = void(*)(T1, T2, T3);
	template<typename T1, typename T2, typename T3, typename T4>
	using Action4 = void(*)(T1, T2, T3, T4);

	class ActionCall
	{
	public:
		virtual void operator()() = 0;
	};

	class Action0Call : public ActionCall
	{
		Action0 m_funtion;
	public:
		Action0Call(Action0 _function) : m_funtion(_function)
		{}
		void operator()()
		{
			m_funtion();
		}
	};

	template<typename T>
	class Action1Call : public ActionCall
	{
		Action1<T> m_funtion;
		T m_parameter1;
	public:
		Action1Call(Action1<T> _function, T _parameter1)
			: m_funtion(_function), m_parameter1(_parameter1)
		{}
		void operator()()
		{
			m_funtion(m_parameter1);
		}
	};

	template<typename T1, typename T2>
	class Action2Call : public ActionCall
	{
		Action2<T1, T2> m_funtion;
		T1 m_parameter1;
		T2 m_parameter2;
	public:
		Action2Call(Action2<T1, T2> _function, T1 _parameter1, T2 _parameter2)
			: m_funtion(_function), m_parameter1(_parameter1), m_parameter2(_parameter2)
		{}
		void operator()()
		{
			m_funtion(m_parameter1, m_parameter2);
		}
	};

	template<typename T1, typename T2, typename T3>
	class Action3Call : public ActionCall
	{
		Action3<T1, T2, T3> m_funtion;
		T1 m_parameter1;
		T2 m_parameter2;
		T3 m_parameter3;
	public:
		Action3Call(Action3<T1, T2, T3> _function, T1 _parameter1, T2 _parameter2, T3 _parameter3)
			: m_funtion(_function), m_parameter1(_parameter1), m_parameter2(_parameter2), m_parameter3(_parameter3)
		{}
		void operator()()
		{
			m_funtion(m_parameter1, m_parameter2, m_parameter3);
		}
	};

	template<typename T1, typename T2, typename T3, typename T4>
	class Action4Call : public ActionCall
	{
		Action4<T1, T2, T3, T4> m_funtion;
		T1 m_parameter1;
		T2 m_parameter2;
		T3 m_parameter3;
		T4 m_parameter4;
	public:
		Action4Call(Action4<T1, T2, T3, T4> _function, T1 _parameter1, T2 _parameter2, T3 _parameter3, T4 _parameter4)
			: m_funtion(_function), m_parameter1(_parameter1), m_parameter2(_parameter2),
			m_parameter3(_parameter3), m_parameter4(_parameter4)
		{}
		void operator()()
		{
			m_funtion(m_parameter1, m_parameter2, m_parameter3, m_parameter4);
		}
	};
}