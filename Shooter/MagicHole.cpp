#include "stdafx.h"
#include "MagicHole.h"


CMagicHole::CMagicHole()
{
}


CMagicHole::~CMagicHole()
{
}

void CMagicHole::Initialize()
{
	m_pMapBmp = m_pObj->GetBitMap();
	m_tStat = STAT(200);
	INFO tinfo = m_pObj->GetInfo();
	tinfo.fx = WINCX / 2;
	tinfo.fy = WINCY / 4;
	tinfo.fcx = 50;
	tinfo.fcy = 50;

	m_pObj->SetInfo(tinfo);
	m_dwTime = GetTickCount();
	m_pObj->m_bEvade = true;
	m_iBmpAngle = 0;
	m_BmpInfo = INFO(332, 113, 64, 64);
}

int CMagicHole::Progress(INFO& rInfo)
{
	if (rInfo.fx < -200 || rInfo.fx > WINCX + 200 || rInfo.fy < -200 || rInfo.fy > WINCY + 200)
		return 비활성;

	if (m_tStat.iHP <= 0)
		return 비활성;

	m_iBmpAngle += 3;

	return 0;
}

void CMagicHole::Render(HDC hdc)
{
	/*RECT rc = m_pObj->GetRect();
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);*/
	INFO tinfo = m_pObj->GetInfo();
	RotateBlt("Bullet", tinfo, m_BmpInfo, m_iBmpAngle);
}

void CMagicHole::Release()
{
}