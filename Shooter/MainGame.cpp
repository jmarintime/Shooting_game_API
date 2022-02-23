#include "stdafx.h"
#include "MainGame.h"

#include "Define.h"
#include "Device.h"
#include "SceneMgr.h"
#include "KeyMgr.h"

CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	srand(GetTickCount());

	m_hdc = GetDC(g_hWnd);

	GET_SINGLE(CDevice)->Init();
	GET_SINGLE(CSceneMgr)->SetScene(SCE_LOGO);
}

void CMainGame::Progress()
{
	GET_SINGLE(CKeyMgr)->CheckKey();
	GET_SINGLE(CSceneMgr)->Progress();
}

void CMainGame::Render()
{
	GET_SINGLE(CSceneMgr)->Render(m_hdc);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hdc);
	DESTROY_SINGLE(CSceneMgr);
	DESTROY_SINGLE(CKeyMgr);
}