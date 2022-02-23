#include "stdafx.h"
#include "ReverseBullet.h"


CReverseBullet::CReverseBullet()
{
	m_fSpeed = 4.f;
	m_tStat.iAtt = 1;
}


CReverseBullet::~CReverseBullet()
{
}

void CReverseBullet::Initialize()
{
	m_pMapBmp = m_pObj->GetBitMap();
	INFO tinfo = m_pObj->GetInfo();
	tinfo.fcx = 15;
	tinfo.fcy = 15;
	m_fSpeed = 4.f;

	m_pObj->SetInfo(tinfo);
	m_BmpInfo = INFO(m_iType * 16, 47, 16, 16);
}

int CReverseBullet::Progress(INFO & rInfo)
{
	rInfo.fx += cosf(m_fAngle * PI / 180) * m_fSpeed;
	rInfo.fy -= sinf(m_fAngle * PI / 180) * m_fSpeed;

	if (rInfo.fx < -100 || rInfo.fx > WINCX + 100 || rInfo.fy < -100 || rInfo.fy > WINCY + 100)
		return ºñÈ°¼º;

	if (m_fSpeed > -3.5f)
		m_fSpeed -= 0.04f;
	

	return 0;
}

void CReverseBullet::Render(HDC hdc)
{
	/*RECT rc = m_pObj->GetRect();
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);*/
	INFO tinfo = m_pObj->GetInfo();
	TransparentBlt(hdc,
		int((tinfo.fx - tinfo.fcx / 2)),
		int((tinfo.fy - tinfo.fcy / 2)),
		(int)tinfo.fcx, (int)tinfo.fcy,
		(*m_pMapBmp)["Bullet"]->GetMemDC(),
		(int)m_BmpInfo.fx, (int)m_BmpInfo.fy, (int)m_BmpInfo.fcx, (int)m_BmpInfo.fcy,
		RGB(255, 255, 255));
}

void CReverseBullet::Release()
{
}