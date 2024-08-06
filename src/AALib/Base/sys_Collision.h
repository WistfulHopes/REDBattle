#pragma once

class AA_CCollision
{
private:
	const void* m_CollisionFileAddr; // 0x0
	const char* m_ColFileName; // 0x8
protected:
    void SetCollisionFileAddr(const void* addr) { m_CollisionFileAddr = addr; }
public:
	AA_CCollision();
};