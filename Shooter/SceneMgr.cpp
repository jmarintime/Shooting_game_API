#include "stdafx.h"
#include "SceneMgr.h"

#include "Logo.h"
#include "MyMenu.h"
#include "Stage.h"


CSceneMgr::CSceneMgr()
	:m_pScene(NULL)
{
}

CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::SetScene(SCENEID _scene)
{
	::Safe_Delete(m_pScene);

	switch (_scene)
	{
	case SCE_LOGO:
		m_pScene = new CLogo;
		break;
	case SCE_MENU:
		m_pScene = new CMyMenu;
		break;
	case SCE_STAGE:
		m_pScene = new CStage;
		break;
	case SCE_END:
		break;
	default:
		break;
	}

	m_pScene->Initialize();
}

void CSceneMgr::Progress()
{
	m_pScene->Progress();
}

void CSceneMgr::Render(HDC hdc)
{
	m_pScene->Render(hdc);
}

void CSceneMgr::Release()
{
}
