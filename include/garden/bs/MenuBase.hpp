#pragma once

#include "Base.hpp"
#include "../ssys/st/ListNode.hpp"

class MenuBase : public Base
{
protected:
	MenuBase();
	virtual ~MenuBase() override;
	virtual bool CanInitialize() const override;
	virtual ProcessResult Initialize() override;
	virtual bool CanFinalize() const override;
	virtual ProcessResult Finalize() override;
	virtual void HandleFinalizationResult(ProcessResult) override;
	virtual bool CanCalc() const override;
	virtual ProcessResult Calc() override;
	virtual ProcessResult Draw() override;

	virtual void FUN_006ab3d8();
	virtual void OnClose();
	virtual void FUN_006ab3f4();
	virtual void FUN_006ab450();
	virtual void FUN_006ab3e0();
	virtual void FUN_006ab440();
	virtual void FUN_006ab3fc();
	virtual void FUN_006ab3ec();
	virtual void FUN_00767b30();

private:
	class List : public ssys::st::ListNode
	{

	private:

		MenuBase* m_pMenu;
		
	};
	ASSERT_SIZE(List, 0x10);

	List m_List;
	u8 m_Kind;
	bool unk0;
	u8 unk1;
	u8 unk2;
};
ASSERT_SIZE(MenuBase, 0x28);

#endif
