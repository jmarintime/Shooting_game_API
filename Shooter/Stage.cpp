#include "stdafx.h"
#include "Stage.h"

#include "ObjFactory.h"
#include "Device.h"
#include "ObjMgr.h"
#include "CollMgr.h"
#include "TimeLine.h"
#include "resource.h"
#include "SceneMgr.h"

#include "StageBack.h"
#include "Clear.h"
#include "GameOver.h"
#include "Player.h"
#include "Bullet.h"
#include "Monster.h"
#include "Anm1.h"


CStage::CStage()
	:m_pBackGround(NULL)
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	m_MapBmp["BackBuffer"] = (new CBitMap)->LoadBmp(L"../Texture/BackBuffer.bmp");
	m_MapBmp["BackBlack"] = (new CBitMap)->LoadBmp(L"../Texture/BackBufferBlack.bmp");
	m_MapBmp["BackWhite"] = (new CBitMap)->LoadBmp(L"../Texture/BackBufferWhite.bmp");
	m_MapBmp["BackGround"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Back/BackGround.bmp");
	m_MapBmp["Clear"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Clear.bmp");
	m_MapBmp["GameOver"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/GameOver.bmp");

	m_MapBmp["Player"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Player/Characters.bmp");
	m_MapBmp["Player1"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Player/Charic1.bmp");
	m_MapBmp["Player2"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Player/Charic2.bmp");
	m_MapBmp["Player3"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Player/Charic3.bmp");

	m_MapBmp["Monster"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Monster/Enemies.bmp");
	m_MapBmp["Monster2"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Monster/dragon_08.bmp");
	m_MapBmp["Boss"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Monster/Boss.bmp");
	m_MapBmp["Boss1"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Monster/Boss1.bmp");
	m_MapBmp["HPbar"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Monster/HPbar.bmp");
	m_MapBmp["MonWall"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Monster/MonWall.bmp");

	m_MapBmp["Bullet"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Bullet/Bullet.bmp");

	m_MapBmp["Explosion"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Effect/Effect_1.bmp");

	GET_SINGLE(CDevice)->LoadWave(L"../Sound/Stage1.wav");
	GET_SINGLE(CDevice)->LoadWave(L"../Sound/Battle1.wav");
	GET_SINGLE(CDevice)->LoadWave(L"../Sound/Play_Gun.wav");
	GET_SINGLE(CDevice)->LoadWave(L"../Sound/Missile.wav");
	GET_SINGLE(CDevice)->LoadWave(L"../Sound/Game_Clear.wav");
	GET_SINGLE(CDevice)->LoadWave(L"../Sound/Encounter.wav");
	
	m_pBackGround = CObjFactory<CStageBack>::CreateObj();

	CObj* Player = CObjFactory<CPlayer>::CreateObj();
	((CPlayer*)Player)->SetBullet(&m_BulletList[BUL_PLAYER]);
	m_ObjList[OBJ_PLAYER].push_back(Player);

	((CStageBack*)m_pBackGround)->SetPlayer(Player);

	CObj::SetBmp(&m_MapBmp);
	GET_SINGLE(CDevice)->SoundPlay(1, 1);

	GET_SINGLE(CTimeLine)->StageSet(m_ObjList, m_BulletList);

	CreateBullet();
}

int CStage::Progress()
{
	m_pBackGround->Progress();

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (list<CObj*>::iterator iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); )
		{
				if ((*iter)->m_bCheck)
				{
					int iResult = (*iter)->Progress();

					if (iResult == 삭제)
						iter = m_ObjList[i].erase(iter);
					else if (iResult == 정리)
					{
						BulletClear();
						GET_SINGLE(CObjMgr)->AddRenderObj(*iter);
						++iter;
					}
					else if (iResult == 클리어)
					{
						BulletClear();
						GET_SINGLE(CDevice)->SoundStop(0);
						GET_SINGLE(CDevice)->SoundPlay(4, 0);
						iter = m_ObjList[i].erase(iter);
						m_ObjList[OBJ_EFFECT].push_back(CObjFactory<CClear>::CreateObj());
					}
					else if (iResult == 100)
					{
						DestroyWindow(g_hWnd);
						return 0;
					}
					else
					{
						GET_SINGLE(CObjMgr)->AddRenderObj(*iter);
						++iter;
					}
				}
				else
					++iter;
		}
	}
	for (int i = 0; i < BUL_END; ++i)
	{
		for (map<OBJTYPE, list<CObj*>>::iterator iter = m_BulletList[i].begin(); iter != m_BulletList[i].end(); ++iter)
		{
			for (list<CObj*>::iterator iter2 = iter->second.begin(); iter2 != iter->second.end();)
			{
				if ((*iter2)->m_bCheck)
				{
					int iResult = (*iter2)->Progress();

					if (iResult == 삭제)
						iter2 = iter->second.erase(iter2);
					else
					{
						GET_SINGLE(CObjMgr)->AddRenderObj(*iter2);
						++iter2;
					}
				}
				else
					++iter2;
			}
		}
	}

	//몬스터 총알충돌
	for (list<CObj*>::iterator Monster = m_ObjList[OBJ_MONSTER].begin(); Monster != m_ObjList[OBJ_MONSTER].end(); ++Monster)
	{
		if ((*Monster)->m_bCheck)
		{
			for (map<OBJTYPE, list<CObj*>>::iterator iter2 = m_BulletList[BUL_PLAYER].begin(); iter2 != m_BulletList[BUL_PLAYER].end(); ++iter2)
			{
				for (list<CObj*>::iterator Bullet = iter2->second.begin(); Bullet != iter2->second.end(); ++Bullet)
				{
					if ((*Bullet)->m_bCheck)
					{
						if (CCollMgr::CollRcCir(*Monster, *Bullet) && !(*Monster)->m_bEvade)
						{
							((CMonster*)*Monster)->Hit(((CBullet*)*Bullet)->GetDamage());
							(*Bullet)->m_bCheck = false;
						}
					}
				}
			}
		}
	}
	//플레이어 총알충돌
	CObj* Player = m_ObjList[OBJ_PLAYER].front();
	for (map<OBJTYPE, list<CObj*>>::iterator iter = m_BulletList[BUL_MONSTER].begin(); iter != m_BulletList[BUL_MONSTER].end(); ++iter)
	{
		for (list<CObj*>::iterator Bullet = iter->second.begin(); Bullet != iter->second.end(); ++Bullet)
		{
			if ((*Bullet)->m_bCheck)
			{
				if (CCollMgr::Collcircle(Player, *Bullet) && !(Player)->m_bEvade)
				{
					(*Bullet)->m_bCheck = false;
					int i = ((CPlayer*)Player)->Hit();

					if (i == 1)
					{
						m_ObjList[OBJ_EFFECT].push_back(CObjFactory<CGameOver>::CreateObj());
						BulletClear();
						GET_SINGLE(CDevice)->SoundStop(0);
						GET_SINGLE(CDevice)->SoundStop(1);
						GET_SINGLE(CTimeLine)->GameOver();
					}
				}
			}
		}
	}

	GET_SINGLE(CTimeLine)->TimeLineCheck();

	return 0;
}

void CStage::Render(HDC hdc)
{
	m_pBackGround->Render(m_MapBmp["BackBuffer"]->GetMemDC());

	BitBlt(m_MapBmp["BackBlack"]->GetMemDC(), 0, 0, WINCX, WINCY,
		m_MapBmp["BackWhite"]->GetMemDC(),
		0, 0, SRCCOPY);

	GET_SINGLE(CObjMgr)->Render(m_MapBmp["BackBuffer"]->GetMemDC());

	TransparentBlt(m_MapBmp["BackBuffer"]->GetMemDC(),
		0, 0, WINCX, WINCY,
		m_MapBmp["BackBlack"]->GetMemDC(),
		0, 0, WINCX, WINCY,
		RGB(255, 255, 255));

	BitBlt(hdc, 0, 0, WINCX, WINCY,
		m_MapBmp["BackBuffer"]->GetMemDC(),
		0, 0, SRCCOPY);
	

	GET_SINGLE(CObjMgr)->Clear();
}

void CStage::Release()
{
	CSceneObj::Release();
	Safe_Delete(m_pBackGround);

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (list<CObj*>::iterator iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); ++iter)
		{
			Safe_Delete(*iter);
		}
		m_ObjList[i].clear();
	}
	for (int i = 0; i < BUL_END; ++i)
	{
		for (map<OBJTYPE, list<CObj*>>::iterator iter = m_BulletList[i].begin(); iter != m_BulletList[i].end(); ++iter)
		{
			for (list<CObj*>::iterator iter2 = iter->second.begin(); iter2 != iter->second.end();)
			{
				Safe_Delete(*iter2);
			}
		}
		m_ObjList[i].clear();
	}
}

void CStage::BulletClear()
{
	for (map<OBJTYPE, list<CObj*>>::iterator iter = m_BulletList[BUL_MONSTER].begin(); iter != m_BulletList[BUL_MONSTER].end(); ++iter)
	{
		for (list<CObj*>::iterator Bullet = iter->second.begin(); Bullet != iter->second.end(); ++Bullet)
		{
			if ((*Bullet)->m_bCheck)
			{
				(*Bullet)->m_bCheck = false;
			}
		}
	}
}

void CStage::CreateBullet()
{
	CBridge*	pBridge = new CNormalBulletA;

	CObj* pBullet = CObjFactory<CBullet>::CreateObj(0, 0, pBridge);
	pBullet->m_bCheck = false;

	list<CObj*> ObjList;
	ObjList.push_back(pBullet);
	m_BulletList[BUL_MONSTER].insert(make_pair(ABL_NORMAL, ObjList));

	map<OBJTYPE, list<CObj*>>::iterator iter = m_BulletList[BUL_MONSTER].find(ABL_NORMAL);
	for (int i = 0; i < 500; i++)
	{
		CBridge*	pBridge = new CNormalBulletA;

		CObj* pBullet = CObjFactory<CBullet>::CreateObj(0, 0, pBridge);
		pBullet->m_bCheck = false;

		iter->second.push_back(pBullet);
	}
}
