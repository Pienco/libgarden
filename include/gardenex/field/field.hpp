#pragma once

#include <garden/field/FdInfo.hpp>

namespace gardenex::field
{
	constexpr float ToCenterWPos(s32 unitX)
	{
		return static_cast<float>((unitX * FdInfo::unitBaseSize) + FdInfo::unitWorldSizeHalfX);
	}

	constexpr Vector3 ToCenterWPos(s32 x, s32 z)
	{
		return {ToCenterWPos(x), 0.0f, ToCenterWPos(z)};
	}

	constexpr Vector3 ToCenterWPosAndHeight(s32 x, s32 z)
	{
		Vector3 result {ToCenterWPos(x), 0.0f, ToCenterWPos(z)};
		result.y = FdInfo::GetHeight(result);
		return result;
	}

	constexpr Vector3 ToCenterWPos(Vector2i pos)
	{
		return ToCenterWPos(pos.x, pos.y);
	}

	inline Vector2i ToUnit(const Vector3& wpos)
	{
		s32 x, z;
		FdInfo::ToUnit(x, z, wpos);
		return {x, z};
	}

	inline Vector2u8 ToUnit8(const Vector3& wpos)
	{
		s32 x, z;
		FdInfo::ToUnit(x, z, wpos);
		return {static_cast<u8>(x), static_cast<u8>(z)};
	}
}
