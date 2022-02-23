#include "stdafx.h"
#include "TimeLine.h"

#include "ObjFactory.h"
#include "MathMgr.h"
#include "Device.h"

#include "Monster.h"
#include "Effect.h"
#include "Anm1.h"
#include "Anm2.h"
#include "Boss1.h"
#include "MonWall.h"
#include "WormHole.h"
#include "MagicHole.h"

void CTimeLine::StageSet(list<CObj*> _obj[], map<OBJTYPE, list<CObj*>> _list[])
{
	m_pObjList = _obj;
	m_pBulletList = _list;

	m_dwTime = GetTickCount();
	m_iPhase = 0;
	m_iCount = 0;

	m_dwPhaseTime[0] = 5000;
	m_dwPhaseTime[1] = 10000;
	m_dwPhaseTime[2] = 12000;
	m_dwPhaseTime[3] = 15000;
	m_dwPhaseTime[4] = 20000;
	m_dwPhaseTime[5] = 24000;
	m_dwPhaseTime[6] = 28000;
	m_dwPhaseTime[7] = 40000;
}

void CTimeLine::TimeLineCheck()
{
	if (m_dwTime + m_dwPhaseTime[m_iPhase] < GetTickCount() && m_iPhase < 8)
	{
		StageTimeLine();
	}

	/*if (GetAsyncKeyState('Q'))
	{
		CreateMonster<CAnm1>(rand() % WINCX, 100, rand()%4);
	}
	if (GetAsyncKeyState('W') && m_iPhase < 6)
	{
		m_iPhase = 6;
		StageTimeLine();
	}*/
}

void CTimeLine::StageTimeLine()
{
	switch (m_iPhase)
	{
	case 0:
		CreateMonster<CAnm1>(WINCX + 150, 0, 0);
		m_dwPhaseTime[m_iPhase] += 300;
		m_iCount++;
		if (m_iCount == 5)
		{
			m_iPhase++;
			m_iCount = 0;
		}
		break;
	case 1:
		CreateMonster<CAnm1>(-100, -50, 1);
		m_dwPhaseTime[m_iPhase] += 300;
		m_iCount++;
		if (m_iCount == 5)
		{
			m_iPhase++;
			m_iCount = 0;
		}
		break;
	case 2:
		CreateMonster<CAnm2>(200, -150, 0);
		m_iPhase++;
		break;
	case 3:
		CreateMonster<CAnm1>(WINCX + 50, 50, 2);
		m_dwPhaseTime[m_iPhase] += 200;
		m_iCount++;
		if (m_iCount == 8)
		{
			m_iPhase++;
			m_iCount = 0;
		}
		break;
	case 4:
		CreateMonster<CAnm1>(-50, 0, 3);
		m_dwPhaseTime[m_iPhase] += 200;
		m_iCount++;
		if (m_iCount == 8)
		{
			m_iPhase++;
			m_iCount = 0;
		}
		break;
	case 5:
		CreateMonster<CAnm2>(400, -150, 0);
		m_iPhase++;
		break;
	case 6:
		CreateMonster<CAnm1>(WINCX + 100, 0, 0);
		CreateMonster<CAnm1>(-100, 0, 1);
		m_dwPhaseTime[m_iPhase] += 500;
		m_iCount++;
		if (m_iCount == 4)
		{
			m_iPhase++;
			m_iCount = 0;
		}
		break;
	case 7:
		CreateBoss<CBoss1>(WINCX / 2, -100);
		m_iPhase++;
		GET_SINGLE(CDevice)->SoundStop(1);
		GET_SINGLE(CDevice)->SoundPlay(5, 0);
		GET_SINGLE(CDevice)->SoundPlay(0, 1);
		break;
	default:
		break;
	}
}

const CObj* CTimeLine::GetTarget(CObj * _obj, OBJID _id)
{
	CObj*	pTarGet = NULL;

	multimap<float, CObj*> p_MapObj;

	if (_id == OBJ_END)
	{
		for (map<OBJTYPE, list<CObj*>>::iterator iter = m_pBulletList[BUL_MONSTER].begin(); iter != m_pBulletList[BUL_MONSTER].end(); ++iter)
		{
			for (list<CObj*>::iterator Bullet = iter->second.begin(); Bullet != iter->second.end(); ++Bullet)
			{
				float fDistance = CMathMgr::GetDistance(_obj, *Bullet);

				p_MapObj.insert(make_pair(fDistance, *Bullet));
			}
		}
	}
	else
	{
		for (list<CObj*>::iterator iter = m_pObjList[_id].begin(); iter != m_pObjList[_id].end(); ++iter)
		{
 			float fDistance = CMathMgr::GetDistance(_obj, *iter);

			p_MapObj.insert(make_pair(fDistance, *iter));
		}
	}
	multimap<float, CObj*>::iterator Mapiter = p_MapObj.begin();
	if (!(Mapiter == p_MapObj.end()))
		pTarGet = Mapiter->second;
	else
	{
		p_MapObj.clear();

		return NULL;
	}

	p_MapObj.clear();

	return pTarGet;
}

template<typename T>
inline void CTimeLine::CreateMonster(float _x, float _y, int _phase)
{
	CBridge*	pBridge = new T;
	((CMonster_Bridge*)pBridge)->SetPhase(_phase);
	((CMonster_Bridge*)pBridge)->SetBullet(&m_pBulletList[BUL_MONSTER]);
	((CMonster_Bridge*)pBridge)->SetTarget(m_pObjList[OBJ_PLAYER].front());
	((CMonWall*)pBridge)->SetList(&m_pBulletList[BUL_PLAYER]);

	CObj* pMonster = CObjFactory<CMonster>::CreateObj(_x, _y, pBridge);
	pMonster->m_bCheck = true;
	

	m_pObjList[OBJ_MONSTER].push_back(pMonster);
}

template<typename T>
inline void CTimeLine::CreateBoss(float _x, float _y)
{
	CBridge*	pBridge = new T;
	((CMonster_Bridge*)pBridge)->SetBullet(&m_pBulletList[BUL_MONSTER]);
	((CMonster_Bridge*)pBridge)->SetTarget(m_pObjList[OBJ_PLAYER].front());
	((CBoss1*)pBridge)->CreateWall(CreateWall());
	for (int i = 0; i<3; i++)
		((CBoss1*)pBridge)->CreateWormHole(CreateWormHole());
	for (int i = 0; i<5; i++)
		((CBoss1*)pBridge)->CreateMagicHole(CreateMagicHole());

	CObj* pMonster = CObjFactory<CMonster>::CreateObj(_x, _y, pBridge);
	pMonster->m_bCheck = true;


	m_pObjList[OBJ_MONSTER].push_back(pMonster);
}

CObj * CTimeLine::CreateWall()
{
	CBridge*	pBridge = new CMonWall;
	((CMonster_Bridge*)pBridge)->SetBullet(&m_pBulletList[BUL_MONSTER]);
	((CMonster_Bridge*)pBridge)->SetTarget(m_pObjList[OBJ_PLAYER].front());
	((CMonWall*)pBridge)->SetList(&m_pBulletList[BUL_PLAYER]);

	CObj* pWall = CObjFactory<CMonster>::CreateObj(0, 0, pBridge);
	pWall->m_bCheck = false;

	return pWall;
}

CObj * CTimeLine::CreateWormHole()
{
	CBridge*	pBridge = new CWormHole;
	((CMonster_Bridge*)pBridge)->SetBullet(&m_pBulletList[BUL_MONSTER]);
	((CMonster_Bridge*)pBridge)->SetTarget(m_pObjList[OBJ_PLAYER].front());
	((CWormHole*)pBridge)->SetList(&m_pBulletList[BUL_PLAYER]);

	CObj* pWormHole = CObjFactory<CMonster>::CreateObj(0, 0, pBridge);
	pWormHole->m_bCheck = false;

	return pWormHole;
}

CObj * CTimeLine::CreateMagicHole()
{
	CBridge*	pBridge = new CMagicHole;

	CObj* pMagicHole = CObjFactory<CEffect>::CreateObj(0, 0, pBridge);
	pMagicHole->m_bCheck = false;

	return pMagicHole;
}

CTimeLine::CTimeLine()
{
}


CTimeLine::~CTimeLine()
{
}
