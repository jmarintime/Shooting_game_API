#pragma once
#include "Obj.h"

class CBridge;
class CMonster : public CObj
{
private:
	CBridge*	m_pBridge;
public:
	void SetBridge(CBridge* m_pBridge) { this->m_pBridge = m_pBridge; }

	void Hit(int _damage);

public:
	virtual void Initialize();
	virtual int Progress();
	virtual void Render(HDC hdc);
	virtual void Release();
public:
	CMonster();
	virtual ~CMonster();
};
