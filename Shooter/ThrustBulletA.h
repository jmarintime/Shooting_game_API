#pragma once
#include "Bullet_Bridge.h"

class CThrustBulletA : public CBullet_Bridge
{
private:
	CObj*	m_pTarget;
	int		m_iLostTime;
public:
	void	SetTarget(CObj* _target) { m_pTarget = _target; }
	void	SetTime(int _time) { m_iLostTime = _time; }
	
public:
	virtual void Initialize();
	virtual int Progress(INFO& rInfo);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual CBridge* Clone() { return new CThrustBulletA(*this); }
	virtual void	SetSpeed(float _speed = 1.f) { m_fSpeed = _speed; }

public:
	CThrustBulletA();
	~CThrustBulletA();
};

