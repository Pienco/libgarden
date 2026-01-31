#pragma once

#include "FieldName.hpp"
#include "types.hpp"

class FdInfo
{
public:
	
	static constexpr u32 unitBaseSize = 32;
	static constexpr u32 unitWorldSizeX = unitBaseSize;
	static constexpr u32 unitWorldSizeZ = unitBaseSize;
	static constexpr u32 unitWorldSizeHalfX = unitWorldSizeX / 2;
	static constexpr u32 unitWorldSizeHalfZ = unitWorldSizeZ / 2;

	/**
	 * @return `nullptr` if not available
	 */
	static class Field* GetCurrentField();

	static float GetHeight(const Vector3& wpos, FieldName field = FieldName::CURRENT);
	static float GetHeightDefault(const Vector3& wpos, FieldName field = FieldName::CURRENT);

	static void ToUnit(s32& x, s32& z, const Vector3& wpos);

	static void ToBlockAndLocalUnit(s32& blockX, s32& blockZ, s32& unitX, s32& unitZ, s32 x, s32 z);
};
