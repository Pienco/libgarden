#pragma once

#include "Process.hpp"

#include <concepts>

namespace oml::framework
{
	template<typename T, typename... Args>
	using Create = T* (*)(Args&&... args);

	template<typename T>
	using Destroy = void(*)(T*);

	struct ProcessFactory
	{
		Create<Process> create;
		Destroy<Process> destroy;
	};
	ASSERT_SIZE(ProcessFactory, 8);

	template<std::derived_from<Process> T>
	consteval ProcessFactory MakeFactory()
	{
		return { T::template Create<T>, T::Destroy };
	}

	struct ProcessInfo
	{
		ProcessIndex index;
		const char* name = "";
		ProcessIndex link1 = index;
		ProcessIndex link2 = index;
	};
	ASSERT_SIZE(ProcessInfo, 0xc);

	class ProcessManager
	{
	public:
		static ProcessManager* Get();

		Process* CreateProcess(ProcessIndex index, Process* parent, u32 arg = 0, u8 type = 0);
		Process* CreateProcess(ProcessIndex index, u32 arg = 0, u8 type = 0);

		static constexpr auto* GetFactories() { return s_pFactories; }
		static constexpr auto* GetInfos() { return s_pInfos; }
		static USED const ProcessInfo* GetInfo(ProcessIndex index);

		static USED Process* CallCreate(ProcessIndex index);
		static USED void CallDestroy(ProcessIndex index, Process* proc);
	
	protected:
		static const s32 s_IndexCount;
		static const ProcessFactory* s_pFactories;
		static const ProcessInfo* s_pInfos;

		u8 m_Data[0x11430];
	};
	ASSERT_SIZE(ProcessManager, 0x11430);
}
