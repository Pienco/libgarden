#pragma once

#include <nn/types.h>

namespace state
{
	template<typename T>
	class Base
	{
	public:
		using Func = void(T::*)();

		constexpr Base() = default;
		virtual ~Base() { }
		virtual const char* GetName(Func) const = 0;

	private:
		const char* m_pName;
		bool m_Enabled;
		INSERT_PAD(3);
	};
	ASSERT_SIZE(Base<decltype([]{})>, 0xc);
}
