#include "stdafx.h"
#include "MyButton.h"

#include "Mouse.h"
#include "KeyMgr.h"

CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize()
{
	m_tInfo.fcx = 100;
	m_tInfo.fcy = 40;

	m_iScene = 0;
}

int CMyButton::Progress()
{
	if (PtInRect(&GetRect(), CMouse::GetPos()))
	{
		m_iScene = 0;

		if (GET_SINGLE(CKeyMgr)->GetKey() & KEY_LBUTTON)
		{
			if (m_strDrawID == "Start")
				return 1;

			else if (m_strDrawID == "Exit")
				return 3;
		}
	}
	else
	{
		m_iScene = 1;
	}

	return 0;
}

void CMyButton::Render(HDC hdc)
{
	TransparentBlt(hdc,
		int(m_tInfo.fx - m_tInfo.fcx / 2),
		int(m_tInfo.fy - m_tInfo.fcy / 2),
		(int)m_tInfo.fcx, (int)m_tInfo.fcy,
		(*m_pMapBmp)[m_strDrawID]->GetMemDC(),
		int(m_tInfo.fcx * m_iScene), 0,
		m_tInfo.fcx, m_tInfo.fcy,
		RGB(255, 255, 255));
}

void CMyButton::Release()
{
}
