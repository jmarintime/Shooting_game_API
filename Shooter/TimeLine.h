#pragma once
#include "Include.h"

class CObj;
class CBridge;
class CTimeLine
{
private:
	DWORD	m_dwTime;
	int		m_iPhase;
	int		m_iCount;
	DWORD	m_dwPhaseTime[10];

	list<CObj*>*				m_pObjList;
	map<OBJTYPE, list<CObj*>>*	m_pBulletList;
public:
	void StageSet(list<CObj*> _obj[], map<OBJTYPE, list<CObj*>> _list[]);
	void TimeLineCheck();
	const CObj*	GetTarget(CObj* _obj, OBJID _id);
	void GameOver() { m_iPhase = 8; }

private:
	void StageTimeLine();
	template <typename T>
	void CreateMonster(float _x, float _y, int _phase = 0);
	template<typename T>
	void CreateBoss(float _x, float _y);
	CObj* CreateWall();
	CObj* CreateWormHole();
	CObj* CreateMagicHole();

public:
	DECLARE_SINGETON(CTimeLine);

private:
	CTimeLine();
public:
	~CTimeLine();
};

