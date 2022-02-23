#pragma once
#include "Bullet_Bridge.h"

class CNormalBulletA : public CBullet_Bridge
{
public:
	virtual void Initialize();
	virtual int Progress(INFO& rInfo);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual CBridge* Clone() { return new CNormalBulletA(*this); }
	virtual void	SetSpeed(float _speed = 2.5f) { m_fSpeed = _speed; }

public:
	CNormalBulletA();
	virtual ~CNormalBulletA();
};

