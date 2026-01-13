#pragma once

#include "Base.hpp"
#include "../script/ITalkRecept.hpp"
#include "../state/Mode.hpp"
#include "../sv/SvStep.hpp"

class BsSvMgr : public Base, public ITalkRecept, public state::Mode<BsSvMgr>
{
public:
	static BsSvMgr* Get() { return s_pInstance; }

	class SaveStep : public SvStep<BsSvMgr, SaveStep>
	{
	public:

	private:
	};
	ASSERT_SIZE(SaveStep, 0x60);

	const SaveStep& GetStep() const { return m_Step; }

	static void SetSaveConnectNetHst();
	static void SetSaveConnectNetVst();
	static void SetSaveContinueNetVst();
	static void SetSaveInterruptNetVst();
	static void SetSaveConnectRandomMatchNetHst();
	static void SetSaveConnectRandomMatchNetVst();
	static void SetSaveSeeOffRandomMatchNetHst();
	static void SetSaveSeeOffNetHostRandomMatchNetVst();
	static void SetSaveSeeOffRandomMatchNetVst();
	static void SetSaveStartTourRandomMatchNetHst();
	static void SetSaveStartTourRandomMatchNetVst();

private:
	static BsSvMgr* s_pInstance;

	u32 unknown;
	SaveStep m_Step;
	u8 data[0x20];
};
ASSERT_SIZE(BsSvMgr, 0x138);
