#include "stdafx.h"
#include "Boss1.h"

#include "TimeLine.h"
#include "MonWall.h"
#include "Monster.h"

CBoss1::CBoss1()
{
}


CBoss1::~CBoss1()
{
}

void CBoss1::Initialize()
{
	m_pMapBmp = m_pObj->GetBitMap();
	m_tStat = STAT(10000);
	INFO tinfo = m_pObj->GetInfo();
	tinfo.fcx = 50;
	tinfo.fcy = 60;
	tinfo.iLayer = 0;

	m_pObj->SetInfo(tinfo);
	m_dwTime = GetTickCount();
	m_dwCoolTime = GetTickCount();

	m_fSpeed = 3.f;
	m_fAngle = 270.f;
	m_fShootAngle = 180.f;
	m_pObj->m_bEvade = true;
	m_iPhase = 0;
	m_iPattern = 0;

	m_bReverse = false;

	m_BmpInfo = INFO(2, 2, 90, 110);
}

int CBoss1::Progress(INFO& rInfo)
{
	Phase(rInfo);

	if (rInfo.fy > WINCY / 4 && m_iPhase == 0)
	{
		m_dwTime = GetTickCount();
		m_fSpeed = 0.f;
		m_pObj->m_bEvade = false;
		m_iPhase = 1;
		m_iPattern = rand() % 4 + 1;
	}

	float per = ((float)m_tStat.iHP / (float)m_tStat.iMaxHP);
	if (per < 0.75f && m_iPhase == 1)
	{
		if (!m_pObj->m_bEvade)
		{
			m_dwTime = GetTickCount();
			m_pObj->m_bEvade = true;
			return 정리;
		}
		PhaseShift();
		m_fShootAngle = 90;
	}
	if (per < 0.5f && m_iPhase == 2)
	{
		if (!m_pObj->m_bEvade)
		{
			m_dwTime = GetTickCount();
			m_pObj->m_bEvade = true;
			return 정리;
		}
		PhaseShift();
		m_fShootAngle = 105;
		rInfo.fcx = 150;
		rInfo.fcy = 100;
		m_fAngle = 180;
		m_fSpeed = 1.5f;
		if (m_pWall)
			m_pWall->m_bCheck = false;
	}
	if (per < 0.25f && m_iPhase == 3)
	{
		if (!m_pObj->m_bEvade)
		{
			m_dwTime = GetTickCount();
			m_pObj->m_bEvade = true;
			return 정리;
		}
		PhaseShift();
		m_fShootAngle = 270;
		rInfo.fcx = 50;
		rInfo.fcy = 100;

		if (rInfo.fx > WINCX / 2 + 5)
		{
			rInfo.fx -= 1.5f;
		}
		else if (rInfo.fx < WINCX / 2 - 5)
		{
			rInfo.fx += 1.5f;
		}
		else
			rInfo.fx = WINCX/2;

		m_fSpeed = 0.f;
	}

	if (m_tStat.iHP <= 0)
		return 클리어;

	if(m_pWall)
	if (m_pWall->m_bCheck)
	{
		m_pWall->SetPos(rInfo.fx, rInfo.fy + 100);
		int i = m_pWall->Progress();
		if (i == 삭제)
			Safe_Delete(m_pWall);
	}
	for (list<CObj*>::iterator iter = m_pWormHole.begin(); iter != m_pWormHole.end(); ++iter)
	{
		if ((*iter)->m_bCheck)
		{
			int i = (*iter)->Progress();
			if (i == 비활성)
				(*iter)->m_bCheck = false;
		}
	}


	/*if (GetAsyncKeyState('1'))
	{
		m_iPattern = 1;
	}
	if (GetAsyncKeyState('2'))
	{
		m_iPattern = 2;
	}
	if (GetAsyncKeyState('3'))
	{
		m_iPattern = 3;
	}
	if (GetAsyncKeyState('4'))
	{
		m_iPattern = 4;
	}
	if (GetAsyncKeyState('5'))
	{
		m_iPattern = 5;
	}
	if (GetAsyncKeyState('6'))
	{
		m_iPattern = 6;
	}
	if (GetAsyncKeyState('7'))
	{
		m_iPattern = 7;
	}
	if (GetAsyncKeyState('8'))
	{
		m_iPattern = 8;
	}
	if (GetAsyncKeyState('E'))
	{
		m_tStat.iHP = 240;
	}*/

	return 0;
}

void CBoss1::Phase(INFO& rInfo)
{
	switch (m_iPhase)
	{
	case 0:
		rInfo.fy -= sinf(m_fAngle * PI / 180) * m_fSpeed;
		break;
	case 1:
		break;
	case 2:
		if(m_pWall)
			m_pWall->m_bCheck = true;
		break;
	case 3:
		rInfo.fx += cosf(m_fAngle * PI / 180) * m_fSpeed;
		m_fAngle += 0.5f;
		if (m_pWall)
			m_pWall->m_bCheck = false;
		break;
	case 4:
	{
		m_fAngle += m_bReverse ? 1 : -1;
		m_tStat.iHP++;
		MagicNum = 0;
		for (vector<CObj*>::iterator iter = m_pMagicHole.begin(); iter != m_pMagicHole.end(); ++iter)
		{
			if ((*iter)->m_bCheck)
			{
				MagicNum++;
			}
		}
		MagicAngle = 360 / MagicNum ;
		
		vector<CObj*>::iterator iter = m_pMagicHole.begin();
		for (int i = 0; i < MagicNum; ++iter)
		{
			if ((*iter)->m_bCheck)
			{
				(*iter)->SetPos(rInfo.fx + cosf((MagicAngle * i + m_fAngle) * PI / 180) * 100, rInfo.fy + sinf((MagicAngle * i + m_fAngle) * PI / 180) * 100);
				(*iter)->Progress();
				i++;
			}
		}
		break;
	}
	case 5:
		break;
	default:
		break;
	}
	Pattern();
	if (m_dwTime + 15000 < GetTickCount())
	{
		m_iPattern = 0;
		if (m_dwTime + 20000 < GetTickCount())
		{
			m_dwTime = GetTickCount();
			switch (m_iPhase)
			{
			case 1:
				m_iPattern = rand() % 4 + 1;
				break;
			case 2:
				m_iPattern = rand() % 4 + 1;
				break;
			case 3:
				m_iPattern = rand() % 3 + 5;
				break;
			case 4:
				m_iPattern = 8;
				for (vector<CObj*>::iterator iter = m_pMagicHole.begin(); iter != m_pMagicHole.end(); ++iter)
				{
					if (!((*iter)->m_bCheck))
					{
						(*iter)->m_bCheck = true;
						return;
					}
				}
				break;
			default:
				break;
			}
			m_bReverse = m_bReverse ? false : true;
		}
	}
}

void CBoss1::Pattern()
{
	switch (m_iPattern)
	{
	case 1:
		if (m_dwCoolTime + 60 < GetTickCount())
		{
			m_dwCoolTime = GetTickCount();
			ShootNormal(m_fShootAngle, 2.5f, 0);
			ShootNormal(m_fShootAngle - 60, 2.5f, 1);
			ShootNormal(m_fShootAngle - 120, 2.5f, 2);
			ShootNormal(m_fShootAngle - 180, 2.5f, 3);
			ShootNormal(m_fShootAngle + 60, 2.5f, 4);
			ShootNormal(m_fShootAngle + 120, 2.5f, 5);
			m_fShootAngle += m_bReverse ? -5.7f : 5.7f;
		}
		break;
	case 2:
		if (m_dwCoolTime + 1000 < GetTickCount())
		{
			m_dwCoolTime = GetTickCount();
			int col = rand() % 6;
			for (float i = 0; i < 360; i += 8.f)
			{
				ShootNormal(i + m_fShootAngle, 3.f, col);
			}
			m_fShootAngle -= 0.7f;
			ShootThrust(60, 400);
			ShootThrust(120, 400);
			ShootThrust(0);
			ShootThrust(180);
		}
		break;
	case 3:
		if (m_dwCoolTime + 20 < GetTickCount())
		{
			m_dwCoolTime = GetTickCount();
			ShootNormal(m_fShootAngle, 10.f, 0);
			ShootNormal(m_fShootAngle - 45, 10.f, 1);
			ShootNormal(m_fShootAngle - 90, 10.f, 2);
			ShootNormal(m_fShootAngle - 135, 10.f, 3);
			ShootNormal(m_fShootAngle + 45, 10.f, 4);
			ShootNormal(m_fShootAngle + 90, 10.f, 5);
			ShootNormal(m_fShootAngle + 135, 10.f, 6);
			ShootNormal(m_fShootAngle + 180, 10.f, 7);
			m_fShootAngle += m_bReverse ? -1.0f : 1.0f;
		}
		break;
	case 4:
		if (m_dwCoolTime + 250 < GetTickCount())
		{
			m_dwCoolTime = GetTickCount();
			ShootReverse(m_fShootAngle, 13);
			ShootReverse(m_fShootAngle - 30, 10);
			ShootReverse(m_fShootAngle - 60, 8);
			ShootReverse(m_fShootAngle - 90, 6);
			ShootReverse(m_fShootAngle - 120, 4);
			ShootReverse(m_fShootAngle + 90, 6);
			ShootReverse(m_fShootAngle + 120, 8);
			ShootReverse(m_fShootAngle + 180, 13);
			ShootReverse(m_fShootAngle + 30, 2);
			ShootReverse(m_fShootAngle + 60, 4);
			ShootReverse(m_fShootAngle + 150, 10);
			ShootReverse(m_fShootAngle - 150, 2);
			m_fShootAngle += m_bReverse ? -3.7f : 3.7f;
		}
		break;
	case 5:
		if (m_dwCoolTime + 3000 < GetTickCount())
		{
			m_dwCoolTime = GetTickCount();
			ShootWormHole();
			if (m_bReverse)
			{
				for (float i = WINCX - 50; i >= 50; i -= 25)
				{
					ShootThrust(i, 50, (WINCX - i) * 4 - 1000, 1);
				}
				m_bReverse = false;
			}
			else
			{
				for (float i = 50; i <= WINCX - 50; i += 25)
				{
					ShootThrust(i, 50, i * 4 - 1000, 1);
				}
				m_bReverse = true;
			}
		}
		break;
	case 6:
		if (m_dwCoolTime + 500 < GetTickCount())
		{
			m_dwCoolTime = GetTickCount();
			if (m_bReverse)
			{
				for (float y = 20; y < WINCY; y += 60)
				{
					ShootNormal(-50, y, 0, 3.f, 0);
					ShootNormal(WINCX + 50, y + 15, 180.f, 2.5f, 2);
				}
				m_bReverse = false;
			}
			else
			{
				for (float y = 50; y < WINCY; y += 60)
				{
					ShootNormal(-50, y, 0, 3.f, 5);
					ShootNormal(WINCX + 50, y + 15, 180.f, 2.5f, 7);
				}
				m_bReverse = true;
			}
		}
		break;
	case 7:
		if (m_dwCoolTime + 3000 < GetTickCount())
		{
			m_dwCoolTime = GetTickCount();
			for (float i = 0; i < 360; i += 15.f)
			{
				ShootBounce(i + m_fShootAngle);
			}
			m_fShootAngle += rand() % 21 - 10;
		}
		break;
	case 8:
		if (m_dwCoolTime + 120 < GetTickCount())
		{
			INFO MagicInfo[5];
			m_dwCoolTime = GetTickCount();
			for (int i = 0; i < MagicNum; i++)
			{
				MagicInfo[i] = INFO(m_pMagicHole[i]->GetInfo());
				ShootNormal(MagicInfo[i].fx, MagicInfo[i].fy, MagicAngle * i + m_fAngle + m_fShootAngle, 2.5f, i);
				ShootNormal(MagicInfo[i].fx, MagicInfo[i].fy, MagicAngle * i + m_fAngle + 180 + m_fShootAngle, 2.5f, i);
			}
			m_fShootAngle += m_bReverse ? -0.7f : 0.7f;
		}
		break;
	default:
		break;
	}
}

void CBoss1::PhaseShift()
{
	m_iPattern = 0;
	if (m_dwTime + 5000 < GetTickCount())
	{
		m_iPhase++;
		m_pObj->m_bEvade = false;
		switch (m_iPhase)
		{
		case 1:
			m_iPattern = rand() % 4 + 1;
			break;
		case 2:
			m_iPattern = rand() % 4 + 1;
			break;
		case 3:
			m_iPattern = rand() % 3 + 5;
			break;
		case 4:
			m_iPattern = 8;
			m_pMagicHole[0]->m_bCheck = true;
			m_pMagicHole[1]->m_bCheck = true;
			break;
		default:
			break;
		}
	}
}

void CBoss1::Render(HDC hdc)
{
	INFO tinfo = m_pObj->GetInfo();
	if (m_iPhase == 3)
	{
		TransparentBlt(hdc,
			int((tinfo.fx - 196 / 2)),
			int((tinfo.fy - 114 / 2)),
			196, 114,
			(*m_pMapBmp)["Boss1"]->GetMemDC(),
			0, 0, 196, 114,
			RGB(255, 255, 255));
	}
	TransparentBlt(hdc,
		int((tinfo.fx - m_BmpInfo.fcx / 2)),
		int((tinfo.fy - m_BmpInfo.fcy / 2)),
		(int)m_BmpInfo.fcx, (int)m_BmpInfo.fcy,
		(*m_pMapBmp)["Boss"]->GetMemDC(),
		(int)(m_BmpInfo.fx),
		(int)(m_BmpInfo.fy),
		(int)m_BmpInfo.fcx, (int)m_BmpInfo.fcy,
		RGB(255, 255, 255));

	float bar = ((float)m_tStat.iHP / (float)m_tStat.iMaxHP) * 550.f;
	INFO HPbar = INFO(bar / 2 + 25, 30, bar, 20);
	INFO HPbarBmp = INFO(0, 0, 100, 10);
	RenderBlt("HPbar", HPbar, HPbarBmp);

	if (m_pWall)
		if (m_pWall->m_bCheck)
			m_pWall->Render(hdc);

	for (list<CObj*>::iterator iter = m_pWormHole.begin(); iter != m_pWormHole.end(); ++iter)
	{
		if ((*iter)->m_bCheck)
		{
			(*iter)->Render(hdc);
		}
	}
	for (vector<CObj*>::iterator iter = m_pMagicHole.begin(); iter != m_pMagicHole.end(); ++iter)
	{
		if ((*iter)->m_bCheck)
		{
			(*iter)->Render(hdc);
		}
	}
}

void CBoss1::Release()
{
}

void CBoss1::ShootNormal(float _angle, float _f, int _num)
{
	INFO tinfo = m_pObj->GetInfo();
	CreateBullet<CNormalBulletA>(tinfo.fx, tinfo.fy, _angle, ABL_NORMAL, 0, _f, _num);
}

void CBoss1::ShootNormal(float _x, float _y, float _angle, float _f, int _num)
{
	INFO tinfo = m_pObj->GetInfo();
	CreateBullet<CNormalBulletA>(_x, _y, _angle, ABL_NORMAL, 0, _f, _num);
}

void CBoss1::ShootThrust(float _angle, int _time)
{
	INFO tinfo = m_pObj->GetInfo();
	CreateBullet<CThrustBulletA>(tinfo.fx, tinfo.fy, _angle, ABL_THRUST, _time, 0.f);
}

void CBoss1::ShootThrust(float _x, float _y, int _time, int _type)
{
	CreateBullet<CThrustBulletA>(_x, _y, 270, ABL_THRUST, _time, 0.f, _type);
}

void CBoss1::ShootReverse(float _angle, int _type)
{
	INFO tinfo = m_pObj->GetInfo();
	CreateBullet<CReverseBullet>(tinfo.fx, tinfo.fy, _angle, ABL_REVERSE, 0, 0.f, _type);
}

void CBoss1::ShootWormHole()
{
	INFO tinfo = m_pObj->GetInfo();
	for (list<CObj*>::iterator iter = m_pWormHole.begin(); iter != m_pWormHole.end(); ++iter)
	{
		if (!(*iter)->m_bCheck)
		{
			int randx[4] = { 100, 250, 350, 500 };
			int i = rand() % 4;
			if (HoleX == randx[i])
			{
				if (i == 3)
					i--;
				else
					i++;
			}
			(*iter)->SetPos(randx[i], tinfo.fy + rand() % 100 + 50);
			HoleX = (*iter)->GetInfo().fx;
			(*iter)->Initialize();
			(*iter)->m_bCheck = true;
			return;
		}
	}
}

void CBoss1::ShootBounce(float _angle)
{
	INFO tinfo = m_pObj->GetInfo();
	CreateBullet<CBounceBullet>(tinfo.fx, tinfo.fy, _angle, ABL_BOUNCE);
}
