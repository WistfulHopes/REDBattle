#pragma once
#include <cstdint>

class AA_ListNode
{
private:
	AA_ListNode * m_Next {}; // 0x8
	AA_ListNode * m_Prev {}; // 0x10
	void SetNext(AA_ListNode *);
	void SetPrev(AA_ListNode *);
public:
	AA_ListNode() 
    { 
        m_Next = nullptr;
        m_Prev = nullptr;
    }
	AA_ListNode * GetNext() { return m_Next; }
	AA_ListNode * GetPrev() { return m_Prev; }
};
class AA_LooseList
{
private:
	AA_ListNode * m_Top {}; // 0x8
	AA_ListNode * m_Tail {}; // 0x10
public:
	AA_LooseList(const AA_LooseList &);
	AA_LooseList();
	~AA_LooseList();
	AA_ListNode * GetTop();
	AA_ListNode * GetTail();
	uint32_t GetListCount();
	bool PushTop(AA_ListNode *);
	bool PushTail(AA_ListNode *);
	AA_ListNode * PopTop();
	AA_ListNode * PopTail();
	bool JoinTopList(AA_LooseList *);
	bool JoinTailList(AA_LooseList *);
	bool Separate(AA_ListNode *);
	bool InsertNext(AA_ListNode *, AA_ListNode *);
	bool InsertPrev(AA_ListNode *, AA_ListNode *);
	bool InsertNextList(AA_ListNode *, AA_LooseList *);
	bool SeparateRange(AA_ListNode *, AA_ListNode *);
	bool InsertNextRange(AA_ListNode *, AA_ListNode *, AA_ListNode *);
	AA_LooseList & operator=(const AA_LooseList &);
};
class AA_LooseRingList
{
private:
	AA_ListNode * m_Current {}; // 0x8
	uint32_t m_NodeNum {}; // 0x10
public:
	AA_LooseRingList(const AA_LooseRingList &);
	AA_LooseRingList();
	~AA_LooseRingList();
	AA_ListNode * GetCurrent();
	uint32_t GetListCount();
	bool InsertNextCurrent(AA_ListNode *);
	AA_ListNode * SeparateCurrent();
	AA_ListNode * NextCurrent();
	AA_ListNode * PrevCurrent();
	bool SetCurrent(AA_ListNode *);
	AA_LooseRingList & operator=(const AA_LooseRingList &);
};
class AA_LinearListNode
{
private:
	AA_LinearListNode * m_Next {}; // 0x0
public:
	AA_LinearListNode();
	~AA_LinearListNode();
	void SetNext(AA_LinearListNode *);
	AA_LinearListNode * GetNext();
};
class AA_LinearList
{
private:
	AA_LinearListNode * m_Top {}; // 0x8
public:
	AA_LinearList(const AA_LinearList &);
	AA_LinearList();
	~AA_LinearList();
	AA_LinearListNode * GetTop();
	uint32_t GetListCount();
	void PushTop(AA_LinearListNode *);
	AA_LinearListNode * PopTop();
	AA_LinearList & operator=(const AA_LinearList &);
};