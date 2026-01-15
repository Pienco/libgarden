#pragma once

#include "../bs/BsDebugMenu.hpp"
#include "hook.hpp"

#include <garden/proc/ProcMgr.hpp>

#include <array>

#ifdef GARDENEX_CHECK_EMULATOR
extern "C" Result svcGetSystemInfo(s64*, u32, s32);
#endif

namespace gardenex::detail
{
	using namespace oml::framework;

	using Callback = void(*)();

	struct Context
	{
		static Context& Get() { return s_Instance; }

		Context() = delete;
		~Context() = delete;
		Context(const Context&) = delete;
		Context(Context&&) = delete;
		Context& operator=(const Context&) = delete;
		Context& operator=(Context&&) = delete;

		struct ProcEntry
		{
			ProcessInfo info;
			Create<Process> create;

			constexpr operator bool() const { return create != nullptr; }
		};

		bool Initialize()
		{
			if (initialized) return false;
			initialized = true;

			#ifdef GARDENEX_CHECK_EMULATOR
			{
				s64 out = 0;
				svcGetSystemInfo(&out, 0x20000, 0);
				isEmulator = out;
			}
			#endif

			{
				static constexpr auto call = [](const auto& table) static
				{
					for (auto fn : table)
						if (fn) fn();
				};

				static constexpr auto hookSystemTask = []<auto Context::*Cb, u32* Addr>() static
				{
					Hook(Addr, +[] static NAKED
					{
						asm(R"(
							bl %a0
							ldr pc, [pc, #-0x4]
							.word %a1
						)" : : "i" (+[] static { call(Get().*Cb); }), "i" (Addr + 2));
					});
				};

				extern std::array<u32, 3> systemTaskCalcHook;
				extern std::array<u32, 3> systemTaskDrawAHook;
				extern std::array<u32, 3> systemTaskDrawBHook;
				hookSystemTask.template operator()<&Context::systemTaskCalcCallbacks, &systemTaskCalcHook[0]>();
				hookSystemTask.template operator()<&Context::systemTaskDrawACallbacks, &systemTaskDrawAHook[0]>();
				hookSystemTask.template operator()<&Context::systemTaskDrawBCallbacks, &systemTaskDrawBHook[0]>();
				
				Hook(ProcessManager::GetInfo, ProcessManager_GetInfo);
				Hook(ProcessManager::CallCreate, ProcessManager_CallCreate);
				Hook(ProcessManager::CallDestroy, ProcessManager_CallDestroy);
			}

			return initialized;
		}

		static s32 RegisterCommon(auto& table, const auto& entry)
		{
			for (size_t i = 0; i < table.size(); i++)
			{
				if (!table[i])
				{
					table[i] = entry;
					return i;
				}
			}
			return -1;
		}

		s32 RegisterSystemTaskCalcCallback(Callback fn) { return RegisterCommon(systemTaskCalcCallbacks, fn); }
		s32 RegisterSystemTaskDrawACallback(Callback fn) { return RegisterCommon(systemTaskDrawACallbacks, fn); }
		s32 RegisterSystemTaskDrawBCallback(Callback fn) { return RegisterCommon(systemTaskDrawBCallbacks, fn); }

		template<std::derived_from<Process> T>
		ProcName RegisterProcess()
		{
			s32 index = RegisterCommon(processes, ProcEntry {{}, Process::template Create<T>});
			if (index < 0) return ProcName::COUNT;
			auto name = static_cast<ProcName>(ProcName::USED_COUNT + index);
			processes[index].info = {name};
			return name;
		}

		template<std::derived_from<Process> T>
		T* RegisterAndCreate()
		{
			return CreateCustomProc<T>(RegisterProcess<T>());
		}

		void CreateDebugMenu()
		{
			debugMenu = RegisterAndCreate<gardenex::BsDebugMenu>();
		}

		template<std::derived_from<Process> T>
		static T* CreateCustomProc(ProcName name)
		{
			return static_cast<T*>(oml::framework::ProcessManager::Get()->CreateProcess(name));
		}

		static bool IsCustomProc(ProcessIndex index) { return index >= ProcName::USED_COUNT; }

		static const ProcessInfo* ProcessManager_GetInfo(ProcessIndex index)
		{
			return IsCustomProc(index) 
				? &Get().processes[index - ProcName::USED_COUNT].info
				: &ProcessManager::GetInfos()[index];
		}

		static Process* ProcessManager_CallCreate(ProcessIndex index)
		{
			return IsCustomProc(index) 
				? Get().processes[index - ProcName::USED_COUNT].create()
				: ProcessManager::GetFactories()[index].create();
		}

		static void ProcessManager_CallDestroy(ProcessIndex index, Process* process)
		{
			IsCustomProc(index) 
				? Process::Destroy(process)
				: ProcessManager::GetFactories()[index].destroy(process);
		}

		static constexpr size_t maxCustomProcess = 20;
		static constexpr size_t maxCallback = 4;

		using Callbacks = std::array<Callback, maxCallback>;

		std::array<ProcEntry, maxCustomProcess> processes;
		Callbacks systemTaskCalcCallbacks;
		Callbacks systemTaskDrawACallbacks;
		Callbacks systemTaskDrawA2Callbacks;
		Callbacks systemTaskDrawBCallbacks;
		BsDebugMenu* debugMenu;
		bool initialized;
		bool isEmulator;

		static Context s_Instance;
	};
	static_assert(sizeof(Context) < 0x200);
}
