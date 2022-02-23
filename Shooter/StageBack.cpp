#include "stdafx.h"
#include "StageBack.h"

#include "Player.h"

CStageBack::CStageBack()
{
}


CStageBack::~CStageBack()
{
}

void CStageBack::StageScroll()
{
	CPlayer* pPlayer = static_cast<CPlayer*>(m_pPlayer);

	/*if (pPlayer->GetInfo().fx > m_ptOffset.x + m_Scroll.iright && m_ptScroll.x > -100)
	{
		m_ptScroll.x -= pPlayer->GetSpeed();
		m_ptOffset.x += pPlayer->GetSpeed();
	}
	if (pPlayer->GetInfo().fx < m_ptOffset.x - m_Scroll.ileft && m_ptScroll.x < 100)
	{
		m_ptScroll.x += pPlayer->GetSpeed();
		m_ptOffset.x -= pPlayer->GetSpeed();
	}*/
	m_ptScroll.y += 1;

	if(m_ptScroll.y == 0)
		m_ptScroll.y = -WINCY;
	//m_ptOffset.y -= 1;
}

void CStageBack::Initialize()
{
	m_tInfo = INFO(0, 0, WINCX, WINCY*2);

	m_ptOffset.x = WINCX / 2;
	m_ptOffset.y = WINCY / 2;

	m_Scroll = SCROLL(0, 0, 250, 250);

	m_ptScroll.y = -WINCY;

	m_bCheck = true;
}

int CStageBack::Progress()
{
	StageScroll();

	return 0;
}

void CStageBack::Render(HDC hdc)
{
	BitBlt(hdc,
		int(m_tInfo.fx + m_ptScroll.x),
		int(m_tInfo.fy + m_ptScroll.y),
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		(*m_pMapBmp)["BackGround"]->GetMemDC(),
		0, 0, SRCCOPY);
}

void CStageBack::Release()
{
}
