#pragma once

namespace state
{
	template<typename Ret = void, typename... Args>
	using Function = Ret(*)(Args...);

	template<typename T, typename Ret = void, typename... Args>
	using MemberFunction = Ret(T::*)(Args...);
}
