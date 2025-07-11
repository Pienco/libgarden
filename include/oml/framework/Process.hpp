#ifndef OML_FRAMEWORK_PROCESS_HPP
#define OML_FRAMEWORK_PROCESS_HPP

#include "types.h"

#include <concepts>

namespace oml::framework
{

	enum class Result
	{
		INVALID,
		STOP,
		SUCCESS,
		FAILURE,
	};

	enum ProcessID: u16
	{
		BEGIN = 0,
		USED_COUNT = 0x27f,

		COUNT = 0x29d,
	};

	class Process
	{

	public:

		Process(const Process&) = delete;
		Process& operator=(const Process&) = delete;

		virtual ~Process();

		void Stop();

	protected:
		virtual bool CanInitialize() const;
		virtual Result Initialize();
		virtual void ProcessInitializationResult(Result);
		virtual bool CanFinalize() const;
		virtual Result Finalize();
		virtual void ProcessFinalizationResult(Result);
		virtual bool CanProcess() const;
		virtual Result DoProcess();
		virtual void ProcessProcessingResult(Result);
		virtual bool CanStartup() const;
		virtual Result Startup();
		virtual void ProcessStartupResult(Result);
		virtual void OnNotify();

		friend class ProcessManager;

		Process();

		void* operator new(size_t size);
		void operator delete(void* p);

		void NotifyDone();

		template<std::derived_from<Process> T>
		static Process* Create() { return new T(); }
		static void Destroy(Process*);

	private:

		s32 m_Handle;
		Process* m_pOther;
		ProcessID m_ID;
		u8 m_State;
		u8 m_IsStopped;
		u8 field6_0x10;
		u8 field7_0x11;
		u8 m_Param2;
		u8 field9_0x13;
	};
	ASSERT_SIZE(Process, 0x14);
}

#endif
