#pragma once

#include "Base.hpp"

namespace state
{
	template<typename T, typename TStep>
	class Step : public Base<TStep>
	{
	public:
		using Func = Base<TStep>::Func;

		// using Base<TStep>::GetName;

		virtual ~Step() override;
		virtual const char* GetName(Func) const override { return nullptr; }

		constexpr Func GetState() const { return m_Callback; }

	private:
		Func m_Callback;
		size_t m_CallbackCounter;
		T* m_pObj;
		const void* m_pInfos;
		size_t m_Count;
		u32 unknown;
	};
}
