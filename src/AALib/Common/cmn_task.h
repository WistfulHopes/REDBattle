#pragma once
#include <cstdint>
#include "cmn_list.h"
#include "cmn_typedef.h"

enum TASKSTATUS
{
	TSKST_ACTIVE = 0,
	TSKST_IDLING = 1,
	TSKST_SUISIDEWAIT = 2,
};
class AA_TaskNode : public AA_ListNode
{
private:
	uint32_t m_TaskID {}; // 0x18
	uint32_t m_Priority {}; // 0x1C
	uint32_t m_TaskStatus {}; // 0x20
	CXXBYTE<32> m_TaskName {}; // 0x24
public:
	AA_TaskNode(AA_TaskNode &);
	AA_TaskNode(const AA_TaskNode &);
	AA_TaskNode(const char *);
	int32_t Func();
	void SetPriority(uint32_t);
	uint32_t GetPriority();
	void SetTaskStatus(uint32_t);
	uint32_t GetTaskStatus();
	void SetTaskID(uint32_t);
	uint32_t GetTaskID();
	const char * GetTaskName();
	const CXXBYTE<32> & GetTaskNameC32BYTE();
	void Suicide();
	virtual ~AA_TaskNode();
	AA_TaskNode & operator=(AA_TaskNode &);
	AA_TaskNode & operator=(const AA_TaskNode &);
};
class AA_TaskSearchEngine
{
public:
	bool CheckAgreement(AA_TaskNode *);
	AA_TaskSearchEngine(AA_TaskSearchEngine &);
	AA_TaskSearchEngine(const AA_TaskSearchEngine &);
	AA_TaskSearchEngine();
	AA_TaskSearchEngine & operator=(AA_TaskSearchEngine &);
	AA_TaskSearchEngine & operator=(const AA_TaskSearchEngine &);
};
class AA_TaskList
{
private:
	static uint32_t m_GlobalTaskID {}; // 0xFFFFFFFFFFFFFFFF
protected:
	uint32_t ProductGlobalTaskID();
private:
	AA_LooseList m_NodeList {}; // 0x8
public:
	AA_TaskList(const AA_TaskList &);
	AA_TaskList();
	~AA_TaskList();
	int32_t Execute();
	AA_TaskNode * RegistList(AA_TaskNode *, uint32_t);
	AA_TaskNode * SearchList(AA_TaskSearchEngine *);
	uint32_t ForceAllRelease();
	uint32_t AllSearchForceAllRelease(AA_TaskSearchEngine *);
	uint32_t AllSearchRemoveList(AA_TaskSearchEngine *);
	AA_TaskNode * GetListTop();
	AA_TaskNode * GetListTail();
	AA_TaskList & operator=(const AA_TaskList &);
};
class AA_TaskSearchEngine_ID : public AA_TaskSearchEngine
{
private:
	uint32_t m_KeyID {}; // 0x8
public:
	AA_TaskSearchEngine_ID(AA_TaskSearchEngine_ID &);
	AA_TaskSearchEngine_ID(const AA_TaskSearchEngine_ID &);
	AA_TaskSearchEngine_ID(uint32_t);
	void SetKeyID(uint32_t);
	virtual bool CheckAgreement(AA_TaskNode *);
	AA_TaskSearchEngine_ID & operator=(AA_TaskSearchEngine_ID &);
	AA_TaskSearchEngine_ID & operator=(const AA_TaskSearchEngine_ID &);
};
class AA_TaskSearchEngine_Name : public AA_TaskSearchEngine
{
private:
	CXXBYTE<32> m_KeyName {}; // 0x8
public:
	AA_TaskSearchEngine_Name(AA_TaskSearchEngine_Name &);
	AA_TaskSearchEngine_Name(const AA_TaskSearchEngine_Name &);
	AA_TaskSearchEngine_Name(const char *);
	void SetKeyName(const char *);
	virtual bool CheckAgreement(AA_TaskNode *);
	AA_TaskSearchEngine_Name & operator=(AA_TaskSearchEngine_Name &);
	AA_TaskSearchEngine_Name & operator=(const AA_TaskSearchEngine_Name &);
};
class AA_TaskSearchEngine_PriorityEqual : public AA_TaskSearchEngine
{
private:
	uint32_t m_KeyPriority {}; // 0x8
public:
	AA_TaskSearchEngine_PriorityEqual(AA_TaskSearchEngine_PriorityEqual &);
	AA_TaskSearchEngine_PriorityEqual(const AA_TaskSearchEngine_PriorityEqual &);
	AA_TaskSearchEngine_PriorityEqual(uint32_t);
	void SetKeyPriority(uint32_t);
	virtual bool CheckAgreement(AA_TaskNode *);
	AA_TaskSearchEngine_PriorityEqual & operator=(AA_TaskSearchEngine_PriorityEqual &);
	AA_TaskSearchEngine_PriorityEqual & operator=(const AA_TaskSearchEngine_PriorityEqual &);
};
class AA_TaskSearchEngine_PriorityMask : public AA_TaskSearchEngine
{
private:
	uint32_t m_KeyPriority {}; // 0x8
public:
	AA_TaskSearchEngine_PriorityMask(AA_TaskSearchEngine_PriorityMask &);
	AA_TaskSearchEngine_PriorityMask(const AA_TaskSearchEngine_PriorityMask &);
	AA_TaskSearchEngine_PriorityMask(uint32_t);
	void SetKeyPriority(uint32_t);
	virtual bool CheckAgreement(AA_TaskNode *);
	AA_TaskSearchEngine_PriorityMask & operator=(AA_TaskSearchEngine_PriorityMask &);
	AA_TaskSearchEngine_PriorityMask & operator=(const AA_TaskSearchEngine_PriorityMask &);
};