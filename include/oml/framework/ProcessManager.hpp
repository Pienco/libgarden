#ifndef OML_FRAMEWORK_PROCESSMANAGER_HPP
#define OML_FRAMEWORK_PROCESSMANAGER_HPP

#include "oml/framework/Process.hpp"
#include "util/Factory.hpp"

#include <concepts>

namespace oml::framework
{

	class ProcessManager
	{

	public:

		struct ProcessFactoryDescription
		{
			Creator<Process> creator;
			Destroyer<Process> destroyer = Process::Destroy;
		};
		ASSERT_SIZE(ProcessFactoryDescription, 8);

		template<std::derived_from<Process> T>
		static consteval ProcessFactoryDescription MakeFactoryDescription()
		{
			return { Process::Create<T>, Process::Destroy };
		}

		template<size_t N>
		using ProcessFactoryDescriptions = std::array<ProcessFactoryDescription, N>;

		struct ProcessDescription
		{
			ProcessID index;
			const char* name = "";
			ProcessID link1 = index;
			ProcessID link2 = index;
		};
		ASSERT_SIZE(ProcessDescription, 0xc);

		template<size_t N>
		using ProcessDescriptions = std::array<ProcessDescription, N>;

		static ProcessManager* Get();

		inline static Process* CreateProcess(ProcessID id, s32 unk0 = 0, s32 unk1 = 0)
		{
			return Get()->CreateProcessImpl(id, unk0, unk1);
		}

		static constexpr auto GetFactoryFunctions() { return s_pFactoryFunctions; }
		static constexpr auto GetProcessDescriptions() { return s_pProcessDescriptions; }
	
	private:

		static const s32 s_ProcessIDCount;
		static const ProcessFactoryDescriptions<static_cast<size_t>(ProcessID::DESCRIPTION_AND_FACTORY_COUNT)>* const s_pFactoryFunctions;
		static const ProcessDescriptions<static_cast<size_t>(ProcessID::DESCRIPTION_AND_FACTORY_COUNT)>* const s_pProcessDescriptions;

		static USED Process* CallCreator(ProcessID id);
		static USED void CallDestroyer(ProcessID id, Process* proc);
		static USED const ProcessDescription* GetDescription(ProcessID id);

		Process* CreateProcessImpl(ProcessID id, s32 unk0 = 0, s32 unk1 = 0);
		
		u8 m_Data[0x11430];
	};
	ASSERT_SIZE(ProcessManager, 0x11430);
}

#endif
