#ifndef UTIL_COMMON_HPP
#define UTIL_COMMON_HPP

namespace util
{
	template<auto Value>
	inline constexpr auto make_static = Value;

	template<auto Value>
	inline constinit auto make_mutable_static = Value;


	template<typename... Args>
	struct Empty
	{
		consteval Empty() = default;
		consteval Empty(Args...) { };
	};

	template<typename = void>
	void constexpr_error(const char* = nullptr);
}

#endif