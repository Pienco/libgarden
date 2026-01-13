#pragma once

#include "../net/SystemCallback.hpp"
#include "PlayerNo.hpp"
#include "AvatarId.hpp"

namespace netgame
{

	class AvatarMgr : public net::SystemCallback
	{
	public:

		struct Principal
		{
			u32 GetPrincipalId() const { return principalId; }
			AvatarId GetAvatarId() const { return avatarId; }

			u32 principalId;
			AvatarId avatarId;
		};

		struct AvatarInfoBase : public Principal
		{
			StationId station;
		};

		struct AvatarInfo : public AvatarInfoBase
		{
			void* senderHandle;
			s32 unk;
		};

		s32 GetIndex(const StationId& id) const;
		PlayerNo GetPlayerNo(const StationId& id) const;
		StationId GetStationId(PlayerNo player) const
		{
			if (player < 4) return m_Infos[player].station;
			return {};
		}

		const AvatarInfo* GetAvatarInfo(PlayerNo player) const;

	private:
		struct FriendCode
		{
			StationId station;
			u8 friendCode[8];
		};

		static constexpr size_t count = netgame::MAX_PLAYER_COUNT;

		s32 unk;
		AvatarInfo m_Infos[count];
		AvatarInfoBase m_Bases[count];
		s32 m_State[count];
		FriendCode m_FriendCodes[count];
		StationId m_Station1;
		StationId m_Station2;
		bool unk3;
		s32 unk4;
	};
	ASSERT_SIZE(AvatarMgr, 0x110);
}