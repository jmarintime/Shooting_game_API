#include "stdafx.h"
#include "Logo.h"

#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")
#include "SceneMgr.h"

CLogo::CLogo()
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	//m_hVideo = MCIWndCreate(g_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD, L"../Video/Logo.wmv");

	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, NULL);
	MCIWndPlay(m_hVideo);

	dwTime = 0;
}

int CLogo::Progress()
{
	if (GetAsyncKeyState(VK_RETURN) ||
		GetAsyncKeyState(VK_ESCAPE) ||
		dwTime > 8000)
	{
		GET_SINGLE(CSceneMgr)->SetScene(SCE_MENU);
		return 0;
	}
	dwTime++;

	return 0;
}

void CLogo::Render(HDC hdc)
{
}

void CLogo::Release()
{
	MCIWndClose(m_hVideo);
}
