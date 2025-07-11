#pragma once

#include "stage/Field.hpp"
#include "stage/ID.hpp"

namespace stage
{
	inline ID GetCurrent()
	{
		extern ID s_Current;
		return s_Current;
	}

	inline bool IsCurrent(ID id)
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
	Field* GetField(FieldID id);

	/**
	 * @return `nullptr` if not available
	 */
	inline Field* GetField(ID stage)
	{
		if (const auto field = GetFieldID(stage); field != FieldID::NONE)
			return GetField(field);
		return nullptr;
	}

	/**
	 * @return `nullptr` if not available
	 */
	Field* GetCurrentField();

	float GetHeight(const PositionF& pos, FieldID field = FieldID::NONE);
	float GetHeightDefault(const PositionF& pos, FieldID field = FieldID::NONE);

	s32 GetRandom(s32 end);
}
