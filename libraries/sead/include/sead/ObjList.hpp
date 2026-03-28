#pragma once

#include <sead/new.hpp>
#include <sead/List.hpp>
#include <sead/FreeList.hpp>
#include <sead/PtrUtil.hpp>
#include <algorithm>

namespace sead
{
template <typename T>
class ObjList : public ListImpl
{
public:
    ObjList() = default;

    bool isBufferReady() const { return mFreeList.work() != nullptr; }

    bool isFull() const { return size() >= mMaxNum; }

    T* front() const { return listNodeToObjWithNullCheck(ListImpl::front()); }
    T* back() const { return listNodeToObjWithNullCheck(ListImpl::back()); }

    T* prev(const T* obj) const
    {
        ListNode* prev_node = objToListNode(obj)->prev();
        if (prev_node == &mStartEnd)
            return nullptr;
        return listNodeToObj(prev_node);
    }

    T* next(const T* obj) const
    {
        ListNode* next_node = objToListNode(obj)->next();
        if (next_node == &mStartEnd)
            return nullptr;
        return listNodeToObj(next_node);
    }

    T* nth(s32 n) const { return listNodeToObjWithNullCheck(ListImpl::nth(n)); }

    s32 indexOf(const T* obj) const { return ListImpl::indexOf(objToListNode(obj)); }

    bool isNodeLinked(const T* obj) const { return objToListNode(obj)->isLinked(); }

    class iterator
    {
    public:
        explicit iterator(T* ptr) : mPtr{ptr} {}
        bool operator==(const iterator& other) const { return mPtr == other.mPtr; }
        bool operator!=(const iterator& other) const { return !operator==(other); }
        iterator& operator++()
        {
            constexpr auto offset = Node::getListNodeOffset();
            auto* node = static_cast<ListNode*>(PtrUtil::addOffset(mPtr, offset))->next();
            mPtr = static_cast<T*>(PtrUtil::addOffset(node, -offset));
            return *this;
        }
        T& operator*() const { return *mPtr; }
        T* operator->() const { return mPtr; }

    private:
        T* mPtr;
    };

    iterator begin() const { return iterator(listNodeToObj(mStartEnd.next())); }
    iterator end() const { return iterator(listNodeToObj(const_cast<ListNode*>(&mStartEnd))); }
    iterator begin(T* ptr) const { return iterator(ptr); }

    static constexpr size_t calculateWorkBufferSize(size_t n) { return n * ElementSize; }

private:
    struct Node
    {
        #pragma GCC diagnostic push
		#pragma GCC diagnostic ignored "-Winvalid-offsetof"
        static constexpr auto getListNodeOffset() { return offsetof(Node, node); }
        T item;
        ListNode node;
        #pragma GCC diagnostic pop
    };

    ListNode* objToListNode(T* obj) const
    {
        return static_cast<ListNode*>(PtrUtil::addOffset(obj, Node::getListNodeOffset()));
    }

    const ListNode* objToListNode(const T* obj) const
    {
        return static_cast<const ListNode*>(PtrUtil::addOffset(obj, Node::getListNodeOffset()));
    }

    T* listNodeToObj(ListNode* node) const
    {
        return static_cast<T*>(PtrUtil::addOffset(node, -Node::getListNodeOffset()));
    }

    const T* listNodeToObj(const ListNode* node) const
    {
        return static_cast<const T*>(PtrUtil::addOffset(node, -Node::getListNodeOffset()));
    }

    T* listNodeToObjWithNullCheck(ListNode* node) const
    {
        return node ? listNodeToObj(node) : nullptr;
    }

    const T* listNodeToObjWithNullCheck(const ListNode* node) const
    {
        return node ? listNodeToObj(node) : nullptr;
    }

    static constexpr size_t ElementSize = std::max(sizeof(Node), FreeList::cPtrSize);

    sead::FreeList mFreeList;
    s32 mMaxNum = 0;
};

template <typename T, s32 N>
class FixedObjList : public ObjList<T>
{
public:
    FixedObjList() : ObjList<T>(N, &mWork) {}

    // These do not make sense for a *fixed* array.
    void setBuffer(s32 ptrNumMax, void* buf) = delete;
    void allocBuffer(s32 ptrNumMax, Heap* heap, s32 alignment = sizeof(void*)) = delete;
    bool tryAllocBuffer(s32 ptrNumMax, Heap* heap, s32 alignment = sizeof(void*)) = delete;
    void freeBuffer() = delete;

private:
    std::aligned_storage_t<ObjList<T>::calculateWorkBufferSize(N),
                           std::max(alignof(T), alignof(T*))>
        mWork;
};

}  // namespace sead
