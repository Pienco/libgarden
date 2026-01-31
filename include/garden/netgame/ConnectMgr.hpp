#pragma once

#include <nn/types.h>

namespace netgame
{

	class ConnectMgr
	{

	public:

		enum Connection : u8
		{
			LOCAL,
			FRIEND_MATCH,
			RANDOM_MATCH,
			BEST_FRIEND,
			DATASTORE,
			INDEPENDENT,
			NONE
		};

		bool Connect(Connection connection);
		bool IsConnected(Connection connection) const;
		bool Disconnect(Connection connection);

	private:

		u8 data[0xc];
	};
	ASSERT_SIZE(ConnectMgr, 0xc);
}