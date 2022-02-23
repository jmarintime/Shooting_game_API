#pragma once
#include "Bullet_Bridge.h"

class CNormalBullet : public CBullet_Bridge
{
public:
	virtual void Initialize();
	virtual int Progress(INFO& rInfo);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual CBridge* Clone() { return new CNormalBullet(*this); }
	virtual void	SetSpeed(float _speed = 20.f) { m_fSpeed = _speed; }

public:
	CNormalBullet();
	virtual ~CNormalBullet();
};

