#ifndef SSYS_ST_LIST_HPP
#define SSYS_ST_LIST_HPP

#include "ssys/st/ListNode.hpp"

namespace ssys::st
{

	class List
	{
	
	public:

		virtual constexpr ~List() { }

	private:

		ListNode* m_pFirst;
		ListNode* m_pLast;
	};
	ASSERT_SIZE(List, 0xc);
}

#endif
