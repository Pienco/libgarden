#pragma once

#include "Field.hpp"

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
	 * @return `nullptr` if not available
	 */
	Field* GetField(FieldName field);

	/**
	 * @return `nullptr` if not available
	 */
	inline Field* GetField(Name stage)
	{
		if (const auto field = GetFieldName(stage); field != FieldName::NONE)
			return GetField(field);
		return nullptr;
	}

	/**
	 * @return `nullptr` if not available
	 */
	Field* GetCurrentField();

	float GetHeight(const PositionF& pos, FieldName field = FieldName::CURRENT);
	float GetHeightDefault(const PositionF& pos, FieldName field = FieldName::CURRENT);

	s32 GetRandom(s32 end);
}
