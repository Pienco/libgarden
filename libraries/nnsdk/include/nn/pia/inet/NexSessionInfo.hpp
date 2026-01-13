#pragma once

#include <nn/pia/session/ISessionInfo.hpp>

namespace nn::pia::inet
{
	class NexSessionInfo : public session::ISessionInfo
	{
	public:
		virtual ~NexSessionInfo() override;
		virtual u32 GetGameMode() const override;
		virtual u32 GetSessionId() const override;
		virtual u32 GetCurrentParticipants() const override;
		virtual u32 GetMinParticipants() const override;
		virtual u32 GetMaxParticipants() const override;
		virtual bool IsOpened() const override;
		virtual void Clear();
		virtual void Unk();
		virtual Result GetApplicationData(void* buf, size_t bufSize) const;
		virtual size_t GetApplicationDataSize() const;
		virtual Result GetAttribute(u32* value, u32 index);
		virtual Result GetUnkData(void* buf, size_t bufSize) const;
		virtual size_t GetUnkDataSize() const;
	};
}