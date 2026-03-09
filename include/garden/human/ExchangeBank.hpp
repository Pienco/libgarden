#pragma once

#include "ExchangeBankBase.hpp"
#include "DoubleBank.hpp"
#include "ExchangeBankKeywordFgNameEx.hpp"

template<size_t HeapSize, typename VramConfig, typename Keyword, bool UnknownBool>
class ExchangeBank : public DoubleBank<HeapSize, false, VramConfig>, public ExchangeBankBase
{
public:
	virtual ~ExchangeBank() override;
	virtual bool Vfun_8(size_t index) override;

	virtual void Vfun_c(const Keyword&, size_t) { }
	virtual bool LoadResource(const Keyword&, size_t) { return true; }
	virtual u8 LoadResourceSplit(const Keyword&, size_t) { return 1; }
	virtual bool Initialize(const Keyword&, size_t, bool) { return true; }
	virtual bool Finalize(const Keyword&, size_t) { return true; }

public:
	u8 m_ExchangeBit;
	Keyword m_Current;
	u8 unknown0;
	u8 unknown1;
	u8 unknown2;
	u8 unknown3;
	Keyword m_Keywords[2];
	u8 m_Bits[1];
};

struct alignas(4) TestKeyword
{
	u8 data[0x14];
};
using TestBank = ExchangeBank<26275u, BankVramConfig<1800u,4u,6600u,4u,false>, TestKeyword, false>;
using TestFgNameBank = ExchangeBank<18471u,BankVramConfig<600u,2u,3600u,2u,false>,ExchangeBankKeywordFgNameEx<(SvFgName ::Name)32766>,true>;

static_assert(offsetof(TestFgNameBank, TestFgNameBank::m_Current) == 0x26);
static_assert(offsetof(TestBank, TestBank::m_Current) == 0x28);
static_assert(sizeof(ExchangeBank<26275u, BankVramConfig<1800u,4u,6600u,4u,false>, TestKeyword, false>) == 0x6c);
