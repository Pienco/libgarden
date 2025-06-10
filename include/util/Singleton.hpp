#ifndef UTIL_SINGLETON_HPP
#define UTIL_SINGLETON_HPP

#include <type_traits>

namespace util
{

	template<typename T>
	class Singleton
	{
		using Self = Singleton<T>;
		friend T;

	public:

		constexpr Singleton(const Self&) = delete;
		constexpr Singleton(Self&&) = delete;
		constexpr Singleton& operator=(const Self&) = delete;
		constexpr Singleton& operator=(Self&&) = delete;

		static T* Get()
		{
			return s_pInstance;
		}

		static constexpr bool IsValid()
		{
			return s_pInstance != nullptr;
		}

	private:

		constexpr Singleton()
		{
			static_assert(std::is_base_of_v<Self, T>);
			s_pInstance = static_cast<T*>(this);
		}

		constexpr ~Singleton()
		{
			s_pInstance = nullptr;
		}

		static inline T* s_pInstance { };
	};

	template<typename T>
	class ConstInitSingleton
	{
		using Self = ConstInitSingleton<T>;
		friend T;

	public:

		constexpr ConstInitSingleton(const Self&) = delete;
		constexpr ConstInitSingleton(Self&&) = delete;
		constexpr ConstInitSingleton& operator=(const Self&) = delete;
		constexpr ConstInitSingleton& operator=(Self&&) = delete;

		static constexpr T* Get()
		{
			return &s_Instance;
		}

	private:

		consteval ConstInitSingleton()
		{
			static_assert(std::is_base_of_v<Self, T>);
		}

		static inline constinit T s_Instance { };
	};
}

#endif