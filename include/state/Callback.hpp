#ifndef STATE_CALLBACK_HPP
#define STATE_CALLBACK_HPP

#include "types.h"

namespace state
{

	template<typename T, typename Ret = void>
	using PointerType = Ret(*)(T*);

	template<typename T, typename Ret = void>
	using MemberPointerType = Ret(T::*)();

	template<typename Func>
	class CallbackBase
	{

	public:

		using FuncType = Func;

		explicit constexpr CallbackBase(Func func): m_Callback { func }
		{
		}

		constexpr CallbackBase() = default;

		constexpr void Set(Func func)
		{
			m_Callback = func;
		}

		constexpr auto& operator=(Func func)
		{
			Set(func);
			return *this;
		}

		constexpr void operator()(auto&&... args)
		{
			m_Callback(std::forward<decltype(args)>(args)...);
		}

		constexpr void operator()(auto&& object, auto&&... args) requires (std::is_member_function_pointer_v<Func>)
		{
			(std::forward<decltype(object)>(object)->*m_Callback)(std::forward<decltype(args)>(args)...);
		}

		constexpr void SetAndCall(Func func, auto&&... args)
		{
			Set(func);
			this->operator()(std::forward<decltype(args)>(args)...);
		}

	private:

		Func m_Callback;
	};

	template<typename T, typename Ret = void>
	using Callback = CallbackBase<PointerType<T, Ret>>;

	template<typename T, typename Ret = void>
	using MemberCallback = CallbackBase<MemberPointerType<T, Ret>>;

}

#endif
