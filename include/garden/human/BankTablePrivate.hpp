#pragma once

#include <nn/types.h>

class BankTablePrivate
{
public:
	virtual bool Vfun_0();
	virtual bool Vfun_4();
	virtual bool CheckBit(size_t index) const;
	virtual void SetBit(size_t index);
	virtual void ClearBit(size_t index);
	virtual void ResetBit();

private:
	s32 m_Size;
};
ASSERT_SIZE(BankTablePrivate, 0x8);
