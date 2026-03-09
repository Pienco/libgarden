#pragma once

#include <sead/Heap.hpp>

class SystemTask
{
public:

	static sead::Heap* GetDebugRootHeap() { return s_pDebugRootHeap; }
	static sead::Heap* GetSystemHeap() { return s_pSystemHeap; }

private:

	static sead::Heap* s_pDebugRootHeap;
	static sead::Heap* s_pSystemHeap;
};
