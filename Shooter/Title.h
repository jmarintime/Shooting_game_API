#pragma once
#include "Obj.h"

class CTitle : public CObj
{
private:
	int m_fAngle;
public:
	virtual void Initialize();
	virtual int Progress();
	virtual void Render(HDC hdc);
	virtual void Release();
public:
	CTitle();
	virtual ~CTitle();
};

