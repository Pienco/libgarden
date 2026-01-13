#pragma once

#include <nn/types.h>

#include <concepts>

namespace oml::framework
{

	enum class Result
	{
		INVALID,
		FAIL,
		SUCCESS,
		RETRY,
	};

	using ProcessIndex = u16;

	class Process
	{
	public:
		Process(const Process&) = delete;
		Process& operator=(const Process&) = delete;

		virtual ~Process();

		void Stop();

		template<std::derived_from<Process> T>
		static Process* Create() { return new T(); }
		static void Destroy(Process*);

	protected:
		virtual bool CanInitialize() const;
		virtual Result Initialize();
		virtual void HandleInitializationResult(Result);
		virtual bool CanFinalize() const;
		virtual Result Finalize();
		virtual void HandleFinalizationResult(Result);
		virtual bool CanCalc() const;
		virtual Result Calc();
		virtual void HandleCalcResult(Result);
		virtual bool CanDraw() const;
		virtual Result Draw();
		virtual void HandleDrawResult(Result);
		virtual void OnStop();

		friend class ProcessManager;

		Process();

		void* operator new(size_t size);
		void operator delete(void* p);

		void StopSelf();

	private:
		s32 m_Handle;
		Process* m_pOther;
		ProcessIndex m_Index;
		u8 m_State;
		u8 m_IsStopped;
		u8 field6_0x10;
		u8 field7_0x11;
		u8 m_Param2;
		u8 field9_0x13;
	};
	ASSERT_SIZE(Process, 0x14);
}
