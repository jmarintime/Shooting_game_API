#pragma once
#include "Monster_Bridge.h"

class CMonWall : public CMonster_Bridge
{
private:
	map<OBJTYPE, list<CObj*>>* m_pPlayerBullet;

public:
	void		SetList(map<OBJTYPE, list<CObj*>>* _list) { m_pPlayerBullet = _list; }

public:
	virtual void Initialize();
	virtual int Progress(INFO& rInfo);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual CBridge* Clone() { return new CMonWall(*this); }
public:
	CMonWall();
	~CMonWall();
};

