#pragma once

#include "Name.hpp"
#include "../field/Field.hpp"

namespace stage
{
	inline Name GetCurrent()
	{
		extern Name s_Current;
		return s_Current;
	}

	inline bool IsCurrent(Name id)
	{
		return id == GetCurrent();
	}

	inline bool IsCurrent(Kind bits)
	{
		return IsKind(bits, GetCurrent());
	}

	/**
	 * @return `0` if not found
	 */
	FieldName GetFieldName(Name stage);

	/**
	 * @return `nullptr` if not available
	 */
	// inline Field* GetField(Name stage)
	// {
	// 	if (const auto field = GetFieldName(stage); field != FieldName::NONE)
	// 		return GetField(field);
	// 	return nullptr;
	// }

	s32 GetRandom(s32 end);
}
