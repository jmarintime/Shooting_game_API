#include "stdafx.h"
#include "GuideBullet.h"

#include "TimeLine.h"
#include "MathMgr.h"

CGuideBullet::CGuideBullet()
{
	m_tStat.iAtt = 3;
}


CGuideBullet::~CGuideBullet()
{
}

void CGuideBullet::Initialize()
{
	m_pMapBmp = m_pObj->GetBitMap();
	INFO tinfo = m_pObj->GetInfo();
	tinfo.fcx = 20;
	tinfo.fcy = 20;
	m_fSpeed = 8.f;

	m_pObj->SetInfo(tinfo);
	m_iGuideAngle = 2.f;
	m_BmpInfo = INFO(33, 225, 32, 32);
}

int CGuideBullet::Progress(INFO & rInfo)
{
	if (m_pTarget == NULL)
	{
		if(m_iType == 0)
			m_pTarget = GET_SINGLE(CTimeLine)->GetTarget(m_pObj, OBJ_MONSTER);
		else if(m_iType == 1)
			m_pTarget = GET_SINGLE(CTimeLine)->GetTarget(m_pObj, OBJ_PLAYER);
		else if (m_iType == 2)
			m_pTarget = GET_SINGLE(CTimeLine)->GetTarget(m_pObj, OBJ_END);
	}
	else
	{
		Guide(rInfo);
	}

	if (m_fAngle < 0)
		m_fAngle += 360;
	if (m_fAngle > 360)
		m_fAngle -= 360;

	rInfo.fx += cosf(m_fAngle * PI / 180) * m_fSpeed;
	rInfo.fy -= sinf(m_fAngle * PI / 180) * m_fSpeed;

	if (rInfo.fx < -100 || rInfo.fx > WINCX + 100 || rInfo.fy < -100 || rInfo.fy > WINCY + 100)
		return ºñÈ°¼º;

	return 0;
}

void CGuideBullet::Render(HDC hdc)
{
	INFO tinfo = m_pObj->GetInfo();
	TransparentBlt(hdc,
		int((tinfo.fx - tinfo.fcx / 2)),
		int((tinfo.fy - tinfo.fcy / 2)),
		(int)tinfo.fcx, (int)tinfo.fcy,
		(*m_pMapBmp)["Monster"]->GetMemDC(),
		(int)m_BmpInfo.fx, (int)m_BmpInfo.fy, (int)m_BmpInfo.fcx, (int)m_BmpInfo.fcy,
		RGB(255, 255, 255));
}

void CGuideBullet::Release()
{
}

void CGuideBullet::Guide(INFO& rInfo)
{
	if (m_pTarget->m_bEvade)
	{
		m_pTarget = NULL;
		return;
	}

	float fTGAngle = CMathMgr::GetAngle(m_pTarget, rInfo);
	float fTGDistance = CMathMgr::GetDistance(m_pTarget, m_pObj);

	if (fTGDistance > 300)
	{
		m_iGuideAngle = 1.5f;
	}
	else if (fTGDistance > 200)
	{
		m_iGuideAngle = 3.f;
	}
	else if (fTGDistance > 100)
	{
		m_iGuideAngle = 5.f;
	}
	else
	{
		m_iGuideAngle = 10.f;
	}

	if ((fTGAngle <= 180 && m_fAngle <= 180) || (fTGAngle > 180 && m_fAngle > 180))
	{
		if (m_fAngle < fTGAngle)
		{
			m_fAngle += m_iGuideAngle;
		}
		else
		{
			m_fAngle -= m_iGuideAngle;
		}
	}
	else
	{
		int a, b;
		if (m_fAngle < fTGAngle)
		{
			a = 0;
			b = 180;
		}
		else
		{
			a = 180;
			b = 0;
		}
		if (m_fAngle - a > fTGAngle - b)
		{
			m_fAngle += m_iGuideAngle;
		}
		else
		{
			m_fAngle -= m_iGuideAngle;
		}
	}
	if (m_dwTime + 1000 < GetTickCount())
	{
		m_dwTime = GetTickCount();
		m_pTarget = NULL;
	}
}
