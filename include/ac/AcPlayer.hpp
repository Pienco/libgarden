#ifndef	AC_ACPLAYER_HPP
#define AC_ACPLAYER_HPP

#include "math/Vector.hpp"

class AcPlayer
{

public:

	inline math::Vector3* GetPosition() { return (math::Vector3*)((u8*)this + 0x14); }
	inline const math::Vector3* GetPosition() const { return (math::Vector3*)((u8*)this + 0x14); }

private:

	u8 m_Data[0x1564];
};
ASSERT_SIZE(AcPlayer, 0x1564);

#endif
