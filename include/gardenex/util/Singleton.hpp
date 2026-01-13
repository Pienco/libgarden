#pragma once

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
}
