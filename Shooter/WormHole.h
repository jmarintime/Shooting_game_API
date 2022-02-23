#pragma once
#include "Monster_Bridge.h"

class CWormHole : public CMonster_Bridge
{
private:
	map<OBJTYPE, list<CObj*>>* m_pPlayerBullet;
	int m_iBmpAngle;

public:
	void		SetList(map<OBJTYPE, list<CObj*>>* _list) { m_pPlayerBullet = _list; }

public:
	virtual void Initialize();
	virtual int Progress(INFO& rInfo);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual CBridge* Clone() { return new CWormHole(*this); }
public:
	CWormHole();
	~CWormHole();
};

