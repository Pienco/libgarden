#ifndef NETGAME_PLAYERSTATE_HPP
#define NETGAME_PLAYERSTATE_HPP

#include "stage/ID.hpp"
#include "math/Vector.hpp"

#include <memory>

namespace netgame
{

	struct ScaledPosition
	{
		static constexpr float scale = 4.0f;
		static constexpr float invScale = 1.0f / scale;

		constexpr void Set(const Vector3& pos)
		{
			position = { static_cast<s16>(pos[0] * scale), static_cast<s16>(pos[2] * scale) };
		}

		constexpr Vector3 Get() const
		{
			return { GetX(), 0.0f, GetZ() };
		}

		float GetX() const { return position[0] * invScale; }
		float GetZ() const { return position[2] * invScale; }

		Vector2s16 position;
	};

	struct PACKED PlayerState
	{
		stage::ID stage;
		u8 anim;
		ScaledPosition position;
		u16 rotation;
		u8 counter;
		u16 flags;
		u8 flags2;
		u8 var;
		u8 pad;
		std::byte actionData[0x18];

		template<typename T> requires (sizeof(T) <= sizeof(actionData) && std::is_trivially_destructible_v<T>)
		T* GetActionData()
		{
			return new (actionData) T;
		}
	};
	ASSERT_SIZE(PlayerState, 0x26);
	ASSERT_OFFSET(PlayerState, PlayerState::actionData, 0xe);
}

#endif
