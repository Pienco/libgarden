#pragma once

#include "ExchangeBank.hpp"

template<size_t HeapSize, typename VramConfig, typename Keyword, typename TResourceLoader, size_t ResLoadersCount, bool UnknownBool>
class ExchangeResBank : public ExchangeBank<HeapSize + (0x180 * ResLoadersCount), VramConfig, Keyword, UnknownBool>
{
public:

private:
	TResourceLoader m_ResourceLoaders[ResLoadersCount][2];
};
