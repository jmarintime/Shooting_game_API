#include "stdafx.h"
#include "MyMenu.h"

#include "Obj.h"
#include "SceneMgr.h"
#include "BackGround.h"
#include "ObjFactory.h"
#include "MyButton.h"
#include "Title.h"


CMyMenu::CMyMenu()
	:m_pBackGround(NULL)
{
}


CMyMenu::~CMyMenu()
{
}

CObj * CMyMenu::CreateButton(float _fx, float _fy, string _drowid)
{
	CObj*	pButton = CObjFactory<CMyButton>::CreateObj(_fx, _fy);
	((CMyButton*)pButton)->SetDrawId(_drowid);

	return pButton;
}

void CMyMenu::Initialize()
{
	m_MapBmp["BackBuffer"] = (new CBitMap)->LoadBmp(L"../Texture/BackBuffer.bmp");
	m_MapBmp["BackGround"] = (new CBitMap)->LoadBmp(L"../Texture/Menu/Back/BackGround.bmp");
	m_MapBmp["Start"] = (new CBitMap)->LoadBmp(L"../Texture/Menu/Button/Start.bmp");
	m_MapBmp["Help"] = (new CBitMap)->LoadBmp(L"../Texture/Menu/Button/Help.bmp");
	m_MapBmp["Exit"] = (new CBitMap)->LoadBmp(L"../Texture/Menu/Button/Exit.bmp");
	m_MapBmp["Title"] = (new CBitMap)->LoadBmp(L"../Texture/Menu/Back/Title.bmp");

	m_pBackGround = new CBackGround;

	m_ButtonList.push_back(CreateButton(WINCX / 2, 600, "Start"));
	m_ButtonList.push_back(CreateButton(WINCX / 2, 680, "Help"));
	m_ButtonList.push_back(CreateButton(WINCX / 2, 760, "Exit"));

	CObj*	pTitle = CObjFactory<CTitle>::CreateObj(WINCX / 2, WINCY / 4);
	m_ButtonList.push_back(pTitle);

	CObj::SetBmp(&m_MapBmp);
}

int CMyMenu::Progress()
{
	int iResult = 0;

	for (list<CObj*>::iterator iter = m_ButtonList.begin(); iter != m_ButtonList.end(); ++iter)
	{
		iResult = (*iter)->Progress();

		switch (iResult)
		{
		case 1:
			GET_SINGLE(CSceneMgr)->SetScene(SCE_STAGE);
			return 0;
		case 3:
			DestroyWindow(g_hWnd);
			return 0;
		default:
			break;
		}
	}

	return 0;
}

void CMyMenu::Render(HDC hdc)
{
	m_pBackGround->Render(m_MapBmp["BackBuffer"]->GetMemDC());

	for (list<CObj*>::iterator iter = m_ButtonList.begin(); iter != m_ButtonList.end(); ++iter)
	{
		(*iter)->Render(m_MapBmp["BackBuffer"]->GetMemDC());
	}

	BitBlt(hdc, 0, 0, WINCX, WINCY, m_MapBmp["BackBuffer"]->GetMemDC(), 0, 0, SRCCOPY);
}

void CMyMenu::Release()
{
	CSceneObj::Release();
	Safe_Delete(m_pBackGround);

	for (list<CObj*>::iterator iter = m_ButtonList.begin(); iter != m_ButtonList.end(); ++iter)
	{
		Safe_Delete(*iter);
	}
	m_ButtonList.clear();
}
