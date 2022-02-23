#include "stdafx.h"
#include "NormalBulletA.h"

#include "resource.h"

CNormalBulletA::CNormalBulletA()
{
	m_fSpeed = 2.5f;
	m_tStat.iAtt = 1;
}


CNormalBulletA::~CNormalBulletA()
{
}

void CNormalBulletA::Initialize()
{
	m_pMapBmp = m_pObj->GetBitMap();
	INFO tinfo = m_pObj->GetInfo();
	tinfo.fcx = 16;
	tinfo.fcy = 16;
	m_fSpeed = 2.5f;

	m_pObj->SetInfo(tinfo);

	m_BmpInfo = INFO(m_iType * 32,47,16,16);
}

int CNormalBulletA::Progress(INFO & rInfo)
{
	rInfo.fx += cosf(m_fAngle * PI / 180) * m_fSpeed;
	rInfo.fy -= sinf(m_fAngle * PI / 180) * m_fSpeed;

	if (rInfo.fx < -100 || rInfo.fx > WINCX + 100 || rInfo.fy < -100 || rInfo.fy > WINCY + 100)
		return ºñÈ°¼º;

	return 0;
}

void CNormalBulletA::Render(HDC hdc)
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

void CNormalBulletA::Release()
{
}