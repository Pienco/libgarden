#pragma once

#include <nn/pia/types.hpp>

namespace nn::pia::session
{
	class ISessionInfo
	{
	public:
		virtual ~ISessionInfo();
		virtual u32 GetGameMode() const = 0;
		virtual u32 GetSessionId() const = 0;
		virtual u32 GetCurrentParticipants() const = 0;
		virtual u32 GetMinParticipants() const = 0;
		virtual u32 GetMaxParticipants() const = 0;
		virtual bool IsOpened() const = 0;
	};
}