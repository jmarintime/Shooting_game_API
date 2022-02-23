#pragma once
#include "Bullet_Bridge.h"

class CBounceBullet : public CBullet_Bridge
{
private:
	int		m_iCount;
	int		m_iBmpAngle;

public:
	virtual void Initialize();
	virtual int Progress(INFO& rInfo);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual CBridge* Clone() { return new CBounceBullet(*this); }
	virtual void	SetSpeed(float _speed = 2.5f) { m_fSpeed = _speed; }

public:
	CBounceBullet();
	virtual ~CBounceBullet();
};

