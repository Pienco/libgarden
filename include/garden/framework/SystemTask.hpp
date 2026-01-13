#pragma once

#include <sead/Heap.hpp>

class SystemTask
{

public:

	static sead::Heap* GetDebugRootHeap() { return s_pDebugRootHeap; }

private:
	static sead::Heap* s_pDebugRootHeap;
};
