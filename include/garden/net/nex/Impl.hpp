#pragma once

#include <nn/pia/session/SessionSearchCriteria.hpp>
#include <nn/pia/session/ISessionInfo.hpp>

namespace net::nex
{
	struct ParticipantInfo
	{
		nn::pia::StationId stationId;
		u32 unk;
		u32 unk2;
	};
	ASSERT_SIZE(ParticipantInfo, 0x10);

	struct MatchInfo
	{
		s64 time;
		ParticipantInfo participants[4];
		nn::pia::StationId localStation;
		nn::pia::StationId hostStation;
		s32 sessionId;
		u32 instanceId;
		u8 participantCount;
		bool notif3Received;
		u32 unk;
	};
	ASSERT_SIZE(MatchInfo, 0x68);

	class Impl
	{
	public:
		using SessionSearchCriteria = nn::pia::session::SessionSearchCriteria;
		using ISessionInfo = nn::pia::session::ISessionInfo;
	
		bool IsConnectedToMatchmakeService() const;
		bool IsNexSessionHost() const;
		bool OpenNexSession(bool notifyFriends, bool setParam = false, u16 param = 0);
		bool CloseNexSession();
		u32 JoinSessionByOwner(const nn::pia::PrincipalId& ownerPid);
		u32 JoinSessionById(u32 sessionId);
		bool JoinRandomSession(u32 attribute);

		size_t SearchSessions(const SessionSearchCriteria& criteria, ISessionInfo** buf, size_t bufSize);
		u8 GetInfo(ParticipantInfo* out, size_t count) const;

	private:
		u8 data[0x2ac];
	};
	ASSERT_SIZE(Impl, 0x2ac);
}