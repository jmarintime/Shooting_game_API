#pragma once
#include "Obj.h"

class CClear : public CObj
{
private:
	int m_iTime;

public:
	virtual void Initialize();
	virtual int Progress();
	virtual void Render(HDC hdc);
	virtual void Release();
public:
	CClear();
	virtual ~CClear();
};

