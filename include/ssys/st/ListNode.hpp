#ifndef SSYS_ST_LISTNODE_HPP
#define SSYS_ST_LISTNODE_HPP

#include "types.h"


namespace ssys::st
{

	class ListNode
	{
	
	public:

		constexpr ListNode() = default;
		virtual ~ListNode();

	private:

		ListNode* m_pPrev { };
		ListNode* m_pNext { };
	};
	ASSERT_SIZE(ListNode, 0xc);
}

#endif
