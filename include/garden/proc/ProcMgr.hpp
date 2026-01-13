#pragma once

#include "../oml/framework/ProcessManager.hpp"

#include "ProcName.hpp"

enum class ProcType : u8
{
	BASE,
	SCENE,
	ACTOR,
};

class ProcMgr
{
public:
	using Process = oml::framework::Process;

	static Process* Create(ProcName name, u32 arg = 0, ProcType type = ProcType::BASE);
	static Process* Create(ProcName name, Process* parent, u32 arg = 0, ProcType type = ProcType::BASE);
};
