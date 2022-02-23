#include "stdafx.h"
#include "ThrustBulletA.h"

#include "MathMgr.h"

CThrustBulletA::CThrustBulletA()
{
	m_tStat.iAtt = 1;
}


CThrustBulletA::~CThrustBulletA()
{
}

void CThrustBulletA::Initialize()
{
	m_pMapBmp = m_pObj->GetBitMap();
	INFO tinfo = m_pObj->GetInfo();
	if (m_iType == 0)
	{
		m_fSpeed = 1.f;
		tinfo.fcx = 20;
		tinfo.fcy = 20;
	}
	if (m_iType == 1)
	{
		m_fSpeed = 0.f;
		tinfo.fcx = 5;
		tinfo.fcy = 5;
	}
	m_iColor = 0;

	m_pObj->SetInfo(tinfo);
	m_BmpInfo = INFO(m_iColor * 32, 111, 32, 32);
}

int CThrustBulletA::Progress(INFO & rInfo)
{
	rInfo.fx += cosf(m_fAngle * PI / 180) * m_fSpeed;
	rInfo.fy -= sinf(m_fAngle * PI / 180) * m_fSpeed;

	if (m_dwTime + 2000 + m_iLostTime < GetTickCount() && m_dwTime + 2050 + m_iLostTime > GetTickCount())
	{
		m_fAngle = CMathMgr::GetAngle(m_pTarget, rInfo);
		switch (m_iType)
		{
		case 0 :
			m_fSpeed = 10.f;
			break;
		case 1:
			m_fSpeed = 15.f;
			break;
		default:
			break;
		}
	}
	switch (m_iType)
	{
	case 0:
		if (m_fSpeed == 1.f)
		{
			rInfo.fcx += 0.2f;
			rInfo.fcy += 0.2f;
		}
		break;
	case 1:
		if (m_fSpeed == 0.f && rInfo.fcx < 20)
		{
			rInfo.fcx += 0.2f;
			rInfo.fcy += 0.2f;
		}
		break;
	default:
		break;
	}

	if (rInfo.fx < -100 || rInfo.fx > WINCX + 100 || rInfo.fy < -100 || rInfo.fy > WINCY + 100)
		return ºñÈ°¼º;

	return 0;
}

void CThrustBulletA::Render(HDC hdc)
{
	INFO tinfo = m_pObj->GetInfo();
	TransparentBlt(hdc,
		int((tinfo.fx - tinfo.fcx / 2)),
		int((tinfo.fy - tinfo.fcy / 2)),
		(int)tinfo.fcx, (int)tinfo.fcy,
		(*m_pMapBmp)["Bullet"]->GetMemDC(),
		(int)m_BmpInfo.fx, (int)m_BmpInfo.fy, (int)m_BmpInfo.fcx, (int)m_BmpInfo.fcy,
		RGB(255, 255, 255));
}

void CThrustBulletA::Release()
{
}