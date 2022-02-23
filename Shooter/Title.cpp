#include "stdafx.h"
#include "Title.h"


CTitle::CTitle()
{
}


CTitle::~CTitle()
{
}

void CTitle::Initialize()
{
	m_tInfo.fcx = 400;
	m_tInfo.fcy = 400;
	m_fAngle = 0;
}

int CTitle::Progress()
{
	m_tInfo.fy += sinf(m_fAngle * PI / 180) * 0.5f;
	m_fAngle += 2;

	return 0;
}

void CTitle::Render(HDC hdc)
{
	TransparentBlt(hdc,
		int(m_tInfo.fx - m_tInfo.fcx / 2),
		int(m_tInfo.fy - m_tInfo.fcy / 2),
		(int)m_tInfo.fcx, (int)m_tInfo.fcy,
		(*m_pMapBmp)["Title"]->GetMemDC(),
		0, 0, m_tInfo.fcx, m_tInfo.fcy,
		RGB(255, 255, 255));
}

void CTitle::Release()
{
}
