#ifndef STATE_BASE_HPP
#define STATE_BASE_HPP

#include "types.h"

namespace state
{
	template<typename T>
	class Base
	{
	
	public:

		using Func = void(T::*)();

		constexpr Base() = default;
		virtual inline ~Base() { }
		virtual const char* GetName(Func) const = 0;

	private:

		const char* m_pName;
		bool m_Enabled;
		INSERT_PAD(3);
	};
	ASSERT_TEMPLATE_SIZE(Base, 0xc);
}

#endif
