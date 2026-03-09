#pragma once

#include "BankTableBase.hpp"
#include "Bank.hpp"

template<typename TBank, size_t Count>
class BankTable : public BankTableBase
{
public:
	virtual ~BankTable();

private:
	TBank m_Banks[Count];
	u8 m_BankBits[(Count + 7) / 8];
};
static_assert(sizeof(BankTable<Bank<11059u, 1u, false, BankVramConfig<0u, 0u, 0u, 0u, false>>, 7u>) == 0x9c);
