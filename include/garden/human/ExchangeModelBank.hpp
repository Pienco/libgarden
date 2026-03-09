#pragma once

#include "ExchangeResBank.hpp"
#include "../g3d/SkeletalModel.hpp"

class ExchangeModelBankBase
{
public:
	virtual g3d::SkeletalModel* GetCurrentModel() = 0;
	virtual const g3d::SkeletalModel* GetCurrentModel() const = 0;
	virtual const void* GetCurrentResource(u32 index) const = 0;

private:
	float unknown = 1.0f;
};
ASSERT_SIZE(ExchangeModelBankBase, 0x8);

template<size_t HeapSize, typename VramConfig, typename Keyword, typename TResourceLoader, size_t ResLoadersCount, bool UnknownBool>
class ExchangeModelBank : public ExchangeResBank<HeapSize, VramConfig, Keyword, TResourceLoader, ResLoadersCount, UnknownBool>, public ExchangeModelBankBase
{
public:
	virtual g3d::SkeletalModel* GetCurrentModel() override;
	virtual const g3d::SkeletalModel* GetCurrentModel() const override;
	virtual const void* GetCurrentResource(u32 index) const override;

private:
	g3d::SkeletalModel m_Models[2];
	// u32 unknown;
};
