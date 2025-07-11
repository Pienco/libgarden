#ifndef AC_DEMOACTOR_HPP
#define AC_DEMOACTOR_HPP

#include "bs/UtlBase.hpp"

#include "Actor.hpp"

class DemoActor : public Actor
{

public:

private:

	u8 m_Node[0x20];
};
ASSERT_SIZE(DemoActor, 0x68);

using UtlBaseDemoActor = UtlBase<DemoActor>;

#endif
