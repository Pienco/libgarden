#pragma once

#include "../ac/Actor.hpp"
#include "UtlBase.hpp"

#include "../sv/SvFgName.hpp"

class BsFtrMgr : UtlBase<Base>
{

public:

	static BsFtrMgr* Get() { return s_pInstance; }

	struct CreateFtrArg
	{
		enum PlaceType
		{
			DEFAULT,
			DISPLAY,
			UNKNOWN_INVISIBLE,
			DISPLAY_2,
			UNKNOWN,
			COUNT
		};

		SvFgName item;
		u8 x;
		u8 y;
		u8 rotation;
		u8 layer;
		u8 placeType;
		u8 pad[3] {};
	};
	ASSERT_SIZE(CreateFtrArg, 0xc);

	static Actor* CreateFtrActor(const CreateFtrArg&);

private:

	static BsFtrMgr* s_pInstance;
};
