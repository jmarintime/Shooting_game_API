#include "stdafx.h"
#include "MonWall.h"

#include "CollMgr.h"

CMonWall::CMonWall()
{
}


CMonWall::~CMonWall()
{
}

void CMonWall::Initialize()
{
	m_pMapBmp = m_pObj->GetBitMap();
	m_tStat = STAT(5000);
	INFO tinfo = m_pObj->GetInfo();
	tinfo.fcx = 70;
	tinfo.fcy = 20;

	m_pObj->SetInfo(tinfo);
	m_dwTime = GetTickCount();

	m_BmpInfo = INFO(0, 0, 70, 20);
}

int CMonWall::Progress(INFO& rInfo)
{
	if (rInfo.fx < -200 || rInfo.fx > WINCX + 200 || rInfo.fy < -200 || rInfo.fy > WINCY + 200)
		return 삭제;

	if (m_tStat.iHP <= 0)
		return 삭제;

	for (map<OBJTYPE, list<CObj*>>::iterator iter = m_pPlayerBullet->begin(); iter != m_pPlayerBullet->end(); ++iter)
	{
		for (list<CObj*>::iterator Bullet = iter->second.begin(); Bullet != iter->second.end(); ++Bullet)
		{
			if ((*Bullet)->m_bCheck)
			{
				if (CCollMgr::CollRcCir(m_pObj, *Bullet))
				{
					m_tStat.iHP--;
					(*Bullet)->m_bCheck = false;
					INFO temp = (*Bullet)->GetInfo();
					if(rand()%5 > 2)
						CreateBullet<CNormalBulletA>(temp.fx, temp.fy, rand() % 121 + 210, ABL_NORMAL, 0, 4.f);
				}
			}
		}
	}

	return 0;
}

void CMonWall::Render(HDC hdc)
{
	INFO tinfo = m_pObj->GetInfo();
	TransparentBlt(hdc,
		int((tinfo.fx - tinfo.fcx / 2)),
		int((tinfo.fy - tinfo.fcy / 2)),
		(int)tinfo.fcx, (int)tinfo.fcy,
		(*m_pMapBmp)["MonWall"]->GetMemDC(),
		(int)(m_BmpInfo.fx),
		(int)(m_BmpInfo.fy),
		(int)tinfo.fcx, (int)tinfo.fcy,
		RGB(255, 255, 255));
}

void CMonWall::Release()
{
}