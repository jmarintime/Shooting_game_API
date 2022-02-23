#pragma once
#include "Monster_Bridge.h"

class CAnm1 : public CMonster_Bridge
{
private:
	void Pattern();
	void Shoot(float _angle);

public:
	virtual void Initialize();
	virtual int Progress(INFO& rInfo);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual CBridge* Clone() { return new CAnm1(*this); }
public:
	CAnm1();
	~CAnm1();
};

