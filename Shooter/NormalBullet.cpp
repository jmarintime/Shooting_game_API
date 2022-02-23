#include "stdafx.h"
#include "NormalBullet.h"


CNormalBullet::CNormalBullet()
{
	m_fSpeed = 20.f;
	m_tStat.iAtt = 1;
}


CNormalBullet::~CNormalBullet()
{
}

void CNormalBullet::Initialize()
{
	m_pMapBmp = m_pObj->GetBitMap();
	INFO tinfo = m_pObj->GetInfo();
	tinfo.fcx = 20;
	tinfo.fcy = 30;

	m_pObj->SetInfo(tinfo);

	m_BmpInfo = INFO(3, 460, 20, 30);
	switch (m_iType)
	{
	case 0:
		m_tStat.iAtt = 2;
		m_BmpInfo.fx = 163;
		break;
	case 1:
		m_tStat.iAtt = 1;
		m_BmpInfo.fx = 195;
		break;
	default:
		break;
	}
}

int CNormalBullet::Progress(INFO & rInfo)
{
	rInfo.fx += cosf(m_fAngle * PI / 180) * m_fSpeed;
	rInfo.fy -= sinf(m_fAngle * PI / 180) * m_fSpeed;

	if (rInfo.fx < -30 || rInfo.fx > WINCX + 30 || rInfo.fy < -30 || rInfo.fy > WINCY + 30)
		return ºñÈ°¼º;

	return 0;
}

void CNormalBullet::Render(HDC hdc)
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

void CNormalBullet::Release()
{
}
