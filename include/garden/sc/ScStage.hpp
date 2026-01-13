#pragma once

#include "common.hpp"
#include "../oml/framework/Process.hpp"

class ScStage
{
public:
	static sead::Heap* GetStageHeap() { return StageCommon::GetStageHeap(); }
	static sead::Heap* GetIslandFieldHeap() { return s_pIslandFieldHeap; }
	static sead::Heap* CreateIslandFieldHeap(sead::Heap* parent);
private:
	static sead::Heap* s_pIslandFieldHeap;
};
