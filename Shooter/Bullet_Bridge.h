#pragma once
#include "Bridge.h"

class CBullet_Bridge : public CBridge
{
protected:
	int		m_iType = 0;
	int		m_iColor;
	
public:
	void			SetType(int _num) { m_iType = _num; }
public:
	virtual void Initialize()PURE;
	virtual int Progress(INFO& rInfo)PURE;
	virtual void Render(HDC hdc)PURE;
	virtual void Release()PURE;
	virtual CBridge* Clone()PURE;
	virtual void	SetSpeed(float _speed)PURE;

protected:

public:
	CBullet_Bridge();
	virtual ~CBullet_Bridge();
};

