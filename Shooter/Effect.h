#pragma once
#include "Obj.h"

class CBridge;
class CEffect : public CObj
{
private:
	CBridge*	m_pBridge;
public:
	void SetBridge(CBridge* m_pBridge) { this->m_pBridge = m_pBridge; }

public:
	virtual void Initialize();
	virtual int Progress();
	virtual void Render(HDC hdc);
	virtual void Release();
public:
	CEffect();
	virtual ~CEffect();
};

