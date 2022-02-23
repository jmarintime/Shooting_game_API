#include "stdafx.h"
#include "Clear.h"


CClear::CClear()
{
}


CClear::~CClear()
{
}

void CClear::Initialize()
{
	m_tInfo = INFO(WINCX/2, 0, 400, 80, 5);

	m_bCheck = true;
	m_iTime = 0;
}

int CClear::Progress()
{
	if (m_tInfo.fy < WINCY / 3)
		m_tInfo.fy++;
	else
		m_iTime += 2;

	if (m_iTime >= 200)
		return 100;

	return 0;
}

void CClear::Render(HDC hdc)
{
	TransparentBlt(hdc,
		int(m_tInfo.fx - m_tInfo.fcx/2),
		int(m_tInfo.fy - m_tInfo.fcy/2),
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		(*m_pMapBmp)["Clear"]->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(255,255,255));
}

void CClear::Release()
{
}
