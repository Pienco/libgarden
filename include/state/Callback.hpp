#ifndef STATE_CALLBACK_HPP
#define STATE_CALLBACK_HPP

#include "types.h"

namespace state
{

	template<typename T, typename Ret = void>
	using PointerType = Ret(*)(T*);

	template<typename T, typename Ret = void>
	using MemberPointerType = Ret(T::*)();

	template<typename Func, typename T, typename Ret = void>
	class CallbackImpl
	{

	public:

		using FuncType = Func;

		constexpr CallbackImpl(Func func): m_Callback { func }
		{
		}

		constexpr void Set(Func func)
		{
			m_Callback = func;
		}

		constexpr void operator()(T* object)
		{
			if constexpr (std::is_same_v<Func, MemberPointerType<T, Ret>>)
			{
				(object->*m_Callback)();
			}
			else 
			{
				m_Callback(object);
			}
		}

		constexpr void SetAndCall(T* object, Func func)
		{
			Set(func);
			this->operator()(object);
		}

	private:

		Func m_Callback;

	};

	template<typename T, typename Ret = void>
	using Callback = CallbackImpl<PointerType<T, Ret>, T, Ret>;

	template<typename T, typename Ret = void>
	using MemberCallback = CallbackImpl<MemberPointerType<T, Ret>, T, Ret>;

}

#endif
