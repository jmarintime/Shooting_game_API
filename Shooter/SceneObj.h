#pragma once
#include "Include.h"

class CSceneObj
{
protected:
	map<string, CBitMap*>	m_MapBmp;
	DWORD	dwTime;

public:
	virtual void Initialize()PURE;
	virtual int Progress()PURE;
	virtual void Render(HDC hdc)PURE;
	virtual void Release()PURE;

public:
	CSceneObj();
	virtual ~CSceneObj();
};

