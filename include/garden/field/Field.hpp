#pragma once

#include "FieldName.hpp"
#include "FieldRect.hpp"
#include "JmpBlock.hpp"
#include "../sv/SvFgBlock.hpp"
#include "../sv/SvBgName.hpp"
#include "../stage/Name.hpp"

class BgInfo
{
public:

private:
	SvBgName m_Name;
	std::array<SvFgBlock*, maxLayerNum> m_Blocks;
};
ASSERT_SIZE(BgInfo, 0xc);

class Field
{
public:

	/**
	 * @return `nullptr` if not available
	 */
	static Field* GetField(FieldName field);

	static stage::Name GetStage(FieldName field);

	const auto& GetBlockBounds() const { return m_BlockBounds; }
	const auto& GetUnitBounds() const { return m_UnitBounds; }

	/**
	 * @return `nullptr` if not available
 	 */
	SvFgName* GetFg(Vector2i pos, u8 layer = 0);

	/**
	 * @return `nullptr` if not available
 	 */
	const SvFgName* GetFg(Vector2i pos, u8 layer = 0) const;

	/**
	 * @return `nullptr` if not available
 	 */
	const SvFgName* GetFg(s32 x, s32 z, u8 layer = 0) const;

	/**
	 * @return `nullptr` if not available
 	 */
	const SvFgName* GetFg(s32 blockX, s32 blockZ, s32 unitX, s32 unitZ, u8 layer = 0) const;

	bool SetFg(const SvFgName& fg, Vector2i pos, u8 layer = 0);

private:
	FieldRect m_BlockBounds;
	FieldRect m_UnitBounds;
	BgInfo* m_pBgs;
	JmpBlock* m_pJmpBlocks;
	void* m_pGrass;
	void* m_pGrass2;
	std::array<SvFgBlock*, maxLayerNum> m_pFgBlocks;
};
ASSERT_SIZE(Field, 0x38);
