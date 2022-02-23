#pragma once
#include "Obj.h"

class CBackGround : public CObj
{
public:
	virtual void Initialize();
	virtual int Progress();
	virtual void Render(HDC hdc);
	virtual void Release();
public:
	CBackGround();
	virtual ~CBackGround();
};

