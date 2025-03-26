#ifndef STATE_MODE_HPP
#define STATE_MODE_HPP

#include "state/Base.hpp"

namespace state
{

	template<typename T>
	class Mode : public Base<T> 
	{

	public:

		using Func = Base<T>::Func;

		struct Info
		{
			const char8_t* names;
			Func transition;
			Func state;
		};

		constexpr Mode() = default;

		virtual inline const char* GetName(Func) const override
		{
			return nullptr;
		}

		void Change(Func f);

		void Call() requires (std::is_base_of_v<Mode<T>, T>)
		{
			const auto func = m_Callback;
			if (func)
				(static_cast<T*>(this)->*func)();
			if (func == m_Callback)
				m_CallbackCounter++;
			else m_CallbackCounter = 0;

		}

	private:

		Func m_Callback;
		size_t m_CallbackCounter;
		bool m_Calling;
		const Info* m_pInfos;
		size_t m_Count;
	};
	ASSERT_TEMPLATE_SIZE(Mode, 0x24);
}
#endif
