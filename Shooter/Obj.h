#pragma once
#include "Include.h"

class CObj
{
protected:
	INFO			m_tInfo;
	static POINT	m_ptScroll;

	static map<string, CBitMap*>*	m_pMapBmp;

public:
	bool		m_bCheck;
	bool		m_bEvade;
public:
	INFO GetInfo() const { return m_tInfo; }
	RECT GetRect();
	POINT GetPoint();

	void SetInfo(INFO _info) { m_tInfo = _info; }
	void SetPos(float _fx, float _fy);
	static void SetBmp(map<string, CBitMap*>* _pMapBmp) { m_pMapBmp = _pMapBmp; }
	map<string, CBitMap*>* GetBitMap() { return m_pMapBmp; }

public:
	virtual void Initialize()PURE;
	virtual int Progress()PURE;
	virtual void Render(HDC hdc)PURE;
	virtual void Release()PURE;
public:
	CObj();
	virtual ~CObj();
};

