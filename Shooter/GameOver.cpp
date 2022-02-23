#include "stdafx.h"
#include "GameOver.h"


CGameOver::CGameOver()
{
}


CGameOver::~CGameOver()
{
}

void CGameOver::Initialize()
{
	m_tInfo = INFO(WINCX / 2, 0, 400, 80, 5);

	m_bCheck = true;
	m_iTime = 0;
}

int CGameOver::Progress()
{
	if (m_tInfo.fy < WINCY / 3)
		m_tInfo.fy++;
	else
		m_iTime += 2;

	if (m_iTime >= 200)
		return 100;

	return Á¤¸®;
}

void CGameOver::Render(HDC hdc)
{
	TransparentBlt(hdc,
		int(m_tInfo.fx - m_tInfo.fcx / 2),
		int(m_tInfo.fy - m_tInfo.fcy / 2),
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		(*m_pMapBmp)["GameOver"]->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(255, 255, 255));
}

void CGameOver::Release()
{
}
