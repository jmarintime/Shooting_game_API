#pragma once
#include "Obj.h"
#include "Bridge.h"
#include "Bullet_Bridge.h"

class CBullet : public CObj
{
private:
	CBridge*	m_pBridge;
public:
	void SetBridge(CBridge* m_pBridge) { this->m_pBridge = m_pBridge; }
	int GetDamage() { return m_pBridge->GetStat().iAtt; }
	CBridge* GetBridge() { return m_pBridge; }

public:
	virtual void Initialize();
	virtual int Progress();
	virtual void Render(HDC hdc);
	virtual void Release();
public:
	CBullet();
	~CBullet();
};

