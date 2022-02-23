#include "stdafx.h"
#include "BackGround.h"



CBackGround::CBackGround()
{
}

CBackGround::~CBackGround()
{
}

void CBackGround::Initialize()
{
}

int CBackGround::Progress()
{
	return 0;
}

void CBackGround::Render(HDC hdc)
{
	BitBlt(hdc,
		0, 0, WINCX, WINCY,
		(*m_pMapBmp)["BackGround"]->GetMemDC(),
		0, 0, SRCCOPY);
}

void CBackGround::Release()
{
}
