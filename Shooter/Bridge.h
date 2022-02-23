#pragma once
#include "Struct.h"
#include "Obj.h"

class CBridge
{
protected:
	CObj*	m_pObj;

	float	m_fAngle;
	float	m_fSpeed;
	DWORD	m_dwTime;

	INFO	m_BmpInfo;

	map<string, CBitMap*>*	m_pMapBmp;
	CBitMap*				m_pBmp;
public:
	STAT	m_tStat;
public:
	void SetObj(CObj* pObj) { m_pObj = pObj; }
	STAT GetStat() { return m_tStat; }
	float GetAngle() { return m_fAngle; }
	void SetAngle(float _fanlge) { m_fAngle = _fanlge; m_dwTime = GetTickCount(); }

protected:
	void RenderBlt(string _string, INFO _info, INFO _bmpinfo);
	void ReverseBlt(string _string, INFO _info, INFO _bmpinfo);
	void RotateBlt(string _string, INFO _info, INFO _bmpinfo, float _angle);

public:
	virtual void Initialize()PURE;
	virtual int Progress(INFO& rInfo)PURE;
	virtual void Render(HDC hdc)PURE;
	virtual void Release()PURE;
	virtual CBridge* Clone()PURE;

public:
	CBridge();
	virtual ~CBridge();
};

