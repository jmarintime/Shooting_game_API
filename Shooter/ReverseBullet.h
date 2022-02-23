#pragma once
#include "Bullet_Bridge.h"

class CReverseBullet : public CBullet_Bridge
{
public:
	virtual void Initialize();
	virtual int Progress(INFO& rInfo);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual CBridge* Clone() { return new CReverseBullet(*this); }
	virtual void	SetSpeed(float _speed = 3.5f) { m_fSpeed = _speed; }

public:
	CReverseBullet();
	~CReverseBullet();
};

