#pragma once
#include "Obj.h"

class CGameOver : public CObj
{
private:
	int m_iTime;

public:
	virtual void Initialize();
	virtual int Progress();
	virtual void Render(HDC hdc);
	virtual void Release();
public:
	CGameOver();
	virtual ~CGameOver();
};

