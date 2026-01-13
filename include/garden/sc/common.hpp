#pragma once

#include <sead/Heap.hpp>

class StageCommon
{
public:
	static sead::Heap* GetStageHeap()
	{
		return s_pStageHeap;
	} 

private:
	static sead::Heap* s_pStageHeap;
};
