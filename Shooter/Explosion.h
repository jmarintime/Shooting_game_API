#pragma once
#include "Effect_Bridge.h"

class CExplosion : public CEffect_Bridge
{

public:
	virtual void Initialize();
	virtual int Progress(INFO& rInfo);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual CBridge* Clone() { return new CExplosion(*this); }

public:
	CExplosion();
	virtual ~CExplosion();
};

