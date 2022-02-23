#pragma once
#include "Monster_Bridge.h"

class CBoss1 : public CMonster_Bridge
{
private:
	float	m_fShootAngle;
	int		m_iPattern;

	CObj*		m_pWall;
	bool		m_bReverse;
	list<CObj*>	m_pWormHole;
	vector<CObj*> m_pMagicHole;

	int MagicNum;
	int MagicAngle;
	int HoleX;

private:
	void Phase(INFO& rInfo);
	void Pattern();
	void PhaseShift();
	void ShootNormal(float _angle, float _f = 0, int _num = 0);
	void ShootNormal(float _x, float _y, float _angle, float _f = 0, int _num = 0);
	void ShootThrust(float _angle, int _time = 0);
	void ShootThrust(float _x, float _y, int _time = 0, int _type = 0);
	void ShootReverse(float _angle, int _type = 0);
	void ShootWormHole();
	void ShootBounce(float _angle);

public:
	void	CreateWall(CObj* _obj) { m_pWall = _obj; }
	void	CreateWormHole(CObj* _obj) { m_pWormHole.push_back(_obj); }
	void	CreateMagicHole(CObj* _obj) { m_pMagicHole.push_back(_obj); }

public:
	virtual void Initialize();
	virtual int Progress(INFO& rInfo);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual CBridge* Clone() { return new CBoss1(*this); }
public:
	CBoss1();
	~CBoss1();
};

