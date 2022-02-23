#pragma once
#include "Bullet_Bridge.h"

class CGuideBullet : public CBullet_Bridge
{
private:
	const CObj*		m_pTarget;
	float			m_iGuideAngle;
private:
	void	Guide(INFO& rInfo);
public:
	void	SetTarget(const CObj* _target) { m_pTarget = _target; }

public:
	virtual void Initialize();
	virtual int Progress(INFO& rInfo);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual CBridge* Clone() { return new CGuideBullet(*this); }
	virtual void	SetSpeed(float _speed = 8.f) { m_fSpeed = _speed; }
public:
	CGuideBullet();
	~CGuideBullet();
};

