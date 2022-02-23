#include "stdafx.h"
#include "Explosion.h"


CExplosion::CExplosion()
{
}


CExplosion::~CExplosion()
{
}

void CExplosion::Initialize()
{
	m_pMapBmp = m_pObj->GetBitMap();
	m_tStat = STAT(200);
	INFO tinfo = m_pObj->GetInfo();
	tinfo.fcx = 30;
	tinfo.fcy = 30;

	m_pObj->SetInfo(tinfo);
	m_dwTime = GetTickCount();
	m_pObj->m_bEvade = true;
	m_BmpInfo = INFO(332, 113, 64, 64);
}

int CExplosion::Progress(INFO& rInfo)
{
	if (rInfo.fx < -200 || rInfo.fx > WINCX + 200 || rInfo.fy < -200 || rInfo.fy > WINCY + 200)
		return 비활성;

	if (m_tStat.iHP <= 0)
		return 비활성;


	return 0;
}

void CExplosion::Render(HDC hdc)
{
	RECT rc = m_pObj->GetRect();
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
	INFO tinfo = m_pObj->GetInfo();
}

void CExplosion::Release()
{
}