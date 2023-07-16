#ifndef SC_COMMON_HPP
#define SC_COMMON_HPP

#include "sead/Heap.hpp"

class StageCommon
{

public:

	static inline sead::Heap* GetStageHeap()
	{
		return s_pStageHeap;
	} 

private:

	static sead::Heap* s_pStageHeap;
};

#endif
