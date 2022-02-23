#pragma once
#include "Bridge.h"

class CEffect_Bridge : public CBridge
{
public:
	virtual void Initialize()PURE;
	virtual int Progress(INFO& rInfo)PURE;
	virtual void Render(HDC hdc)PURE;
	virtual void Release()PURE;
	virtual CBridge* Clone()PURE;
public:
	CEffect_Bridge();
	virtual ~CEffect_Bridge();
};

