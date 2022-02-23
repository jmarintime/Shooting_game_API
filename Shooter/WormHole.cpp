#include "stdafx.h"
#include "WormHole.h"

#include "CollMgr.h"

CWormHole::CWormHole()
{
}


CWormHole::~CWormHole()
{
}

void CWormHole::Initialize()
{
	m_pMapBmp = m_pObj->GetBitMap();
	m_tStat = STAT(200);
	INFO tinfo = m_pObj->GetInfo();
	tinfo.fcx = 50;
	tinfo.fcy = 50;

	m_pObj->SetInfo(tinfo);
	m_dwTime = GetTickCount();
	m_BmpInfo = INFO(334, 0, 64, 64);
	m_iBmpAngle = 0;
}

int CWormHole::Progress(INFO& rInfo)
{
	if (rInfo.fx < -200 || rInfo.fx > WINCX + 200 || rInfo.fy < -200 || rInfo.fy > WINCY + 200)
		return 비활성;

	if (m_tStat.iHP <= 0)
		return 비활성;

	if (rInfo.fcx < 100.f)
	{
		rInfo.fcx += 0.5f;
		rInfo.fcy += 0.5f;
	}
	else
	{
		m_tStat.iHP--;

		for (map<OBJTYPE, list<CObj*>>::iterator iter = m_pPlayerBullet->begin(); iter != m_pPlayerBullet->end(); ++iter)
		{
			for (list<CObj*>::iterator Bullet = iter->second.begin(); Bullet != iter->second.end(); ++Bullet)
			{
				if ((*Bullet)->m_bCheck)
				{
					if (CCollMgr::Collcircle(m_pObj, *Bullet))
					{
						(*Bullet)->m_bCheck = false;
						INFO temp = (*Bullet)->GetInfo();
						CopyBullet(*Bullet);
					}
				}
			}
		}
	}
	m_iBmpAngle += 3;

	return 0;
}

void CWormHole::Render(HDC hdc)
{
	INFO tinfo = m_pObj->GetInfo();
	RotateBlt("Bullet", tinfo, m_BmpInfo, m_iBmpAngle);
}

void CWormHole::Release()
{
}