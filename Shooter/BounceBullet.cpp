#include "stdafx.h"
#include "BounceBullet.h"


CBounceBullet::CBounceBullet()
{
	m_fSpeed = 2.5f;
	m_tStat.iAtt = 1;
}


CBounceBullet::~CBounceBullet()
{
}

void CBounceBullet::Initialize()
{
	m_pMapBmp = m_pObj->GetBitMap();
	INFO tinfo = m_pObj->GetInfo();
	m_iColor = rand()%6 + 1;
	switch (m_iType)
	{
	case 0:
		tinfo.fcx = 25;
		tinfo.fcy = 25;
		m_fSpeed = 2.5f;
		break;
	case 5:
		tinfo.fcx = 20;
		tinfo.fcy = 20;
		m_fSpeed = 12.5f;
		m_iColor = 0;
		break;
	default:
		tinfo.fcx = 25;
		tinfo.fcy = 25;
		m_fSpeed = 2.5f;
		break;
	}

	m_pObj->SetInfo(tinfo);
	m_iCount = 3;
	m_BmpInfo = INFO(32* m_iColor - 2, 268, 32, 32);
	m_iBmpAngle = 0;
}

int CBounceBullet::Progress(INFO & rInfo)
{
	rInfo.fx += cosf(m_fAngle * PI / 180) * m_fSpeed;
	rInfo.fy -= sinf(m_fAngle * PI / 180) * m_fSpeed;

	if (rInfo.fx > WINCX)
	{
		m_fAngle = 180 - m_fAngle;
		rInfo.fx = WINCX - 10;
		m_iCount--;
		m_fSpeed += 0.5f;
	}
	if (rInfo.fx < 0)
	{
		m_fAngle = 180 - m_fAngle;
		rInfo.fx = 10;
		m_iCount--;
		m_fSpeed += 0.5f;
	}
	if (rInfo.fy > WINCY)
	{
		m_fAngle = 360 - m_fAngle;
		rInfo.fy = WINCY - 10;
		m_iCount--;
		m_fSpeed += 0.5f;
	}
	if (rInfo.fy < 0)
	{
		m_fAngle = 360 - m_fAngle;
		rInfo.fy = 10;
		m_iCount--;
		m_fSpeed += 0.5f;
	}
	m_iBmpAngle += 5;

	if (rInfo.fx < -100 || rInfo.fx > WINCX + 100 || rInfo.fy < -100 || rInfo.fy > WINCY + 100 || m_iCount <= 0)
		return ºñÈ°¼º;

	return 0;
}

void CBounceBullet::Render(HDC hdc)
{
	INFO tinfo = m_pObj->GetInfo();
	RotateBlt("Bullet", tinfo, m_BmpInfo, m_iBmpAngle);
}

void CBounceBullet::Release()
{
}