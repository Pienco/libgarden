#pragma once

#include "Bank.hpp"

template<size_t HeapSize, bool UnknownBool, typename VramConfig>
class DoubleBank : public Bank<HeapSize, 2, UnknownBool, VramConfig>
{
public:

};
static_assert(sizeof(DoubleBank<26275u, false, BankVramConfig<1800u, 4u, 6600u, 4u, false>>) == 0x24);
