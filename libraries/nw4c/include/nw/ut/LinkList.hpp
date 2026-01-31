#pragma once

#include <nn/types.h>

namespace nw::ut
{

	struct LinkListNode
	{
		LinkListNode* next {};
		LinkListNode* prev {};
	};

	class LinkListImpl
	{
	public:
		size_t size() const { return m_Count; }

	private:
		size_t m_Count {};
	};

	template<auto Ptr>
	class LinkList { };

	template<typename T, LinkListNode T::* Ptr>
	class LinkList<Ptr> : public LinkListImpl
	{

	private:
		LinkListNode m_Node {&m_Node, &m_Node};
	};

}
