#pragma once

#include <nn/types.h>

namespace net::nex
{

	struct Command
	{
		enum ID : u8
		{
			NONE = 0,
			CONNECT_LOCAL = 1,
			CONNECT_NEX = 2,
			STUB_0 = 0x25,
			STUB_1 = 0x26,
			STUB_2 = 0x27,
			STUB_3 = 0x28,
			STUB_4 = 0x29,
			STUB_5 = 0x2a,
		};

		enum Status : u8
		{
			NOT_DONE = 0,
			DONE = 1,
			FAILED = 2,
		};

		union Param
		{
			u8 raw[0x28];
		};

		void SetDone() { status = Status::DONE; }
		void SetFailed() { status = Status::FAILED; }

		ID id;
		u32 unk;
		Param param;
		u8 processState;
		Status status;
		INSERT_PAD(2);
	};
	ASSERT_SIZE(Command, 0x34);

}