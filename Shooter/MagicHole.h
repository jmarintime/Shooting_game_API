#pragma once
#include "Effect_Bridge.h"

class CMagicHole : public CEffect_Bridge
{
private:
	int							m_iBmpAngle;

public:
	virtual void Initialize();
	virtual int Progress(INFO& rInfo);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual CBridge* Clone() { return new CMagicHole(*this); }
public:
	CMagicHole();
	~CMagicHole();
};

