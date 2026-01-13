#pragma once

#include <nn/types.h>

namespace script
{

	class MsgEngine
	{

	public:

		virtual ~MsgEngine();

	private:

		struct Message
		{
			s32 unk0;
			s32 unk1;
		};

		char16* m_pText;
		void* m_pUnk0;
		Message m_Messages[10];
	};
	ASSERT_SIZE(MsgEngine, 0x5c);
}
