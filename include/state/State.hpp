#ifndef STATE_STATE_HPP
#define STATE_STATE_HPP

#include "state/Function.hpp"
#include "util/concepts.hpp"

namespace state
{
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpmf-conversions"
	#pragma GCC diagnostic ignored "-Wpedantic"

	template<typename T>
	class State
	{

	public:

		using FunctionType = Function<void, T*>;
		using MemberFunctionType = MemberFunction<T>;

		constexpr State(FunctionType func): function { func }
		{
		}

		constexpr State(MemberFunctionType func) : function { (FunctionType)func }
		{
		}

		constexpr State() = default;

		constexpr auto& operator=(FunctionType func)
		{
			function = func;
			return *this;
		}

		constexpr auto& operator=(MemberFunctionType func)
		{
			function = (FunctionType)func;
			return *this;
		}

		friend constexpr bool operator==(util::SimilarTo<State<T>> auto&& left, util::SimilarTo<FunctionType> auto&& right)
		{
			return left.function == right;
		}

		friend constexpr bool operator==(util::SimilarTo<State<T>> auto&& left, util::SimilarTo<MemberFunctionType> auto&& right)
		{
			return left.function == (FunctionType)right;
		}

		constexpr void operator()(auto&&... args)
		{
			function(std::forward<decltype(args)>(args)...);
		}

		// constexpr void operator()(auto&& object, auto&&... args) requires (std::is_member_function_pointer_v<Func>)
		// {
		// 	(std::forward<decltype(object)>(object)->*m_Func)(std::forward<decltype(args)>(args)...);
		// }

	private:

		FunctionType function;
	};
	#pragma GCC diagnostic pop
}

#endif
