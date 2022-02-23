#include "stdafx.h"
#include "Player.h"

#include "KeyMgr.h"
#include "Device.h"
#include "ObjFactory.h"

#include "Bullet.h"
#include "NormalBullet.h"
#include "GuideBullet.h"
#include "ThrustBulletA.h"
#include "BounceBullet.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
	m_tInfo = INFO(WINCX / 2, WINCY - 100, 10, 10, 2);
	m_BmpInfo = INFO(0, 0, 32, 48);
	m_tFrame = FRAME(0, 4, 0, 100);
	m_dwState = STATE_STAND;

	m_fSpeed = 5.f;
	m_dwKey = 0;
	m_dwTime = GetTickCount();
	m_dwShoot = GetTickCount();
	for (int i = 0; i < SKL_END; ++i)
	{
		m_tCount[i] = 50;
	}
	m_fAngle = 90;
	m_iSkillNum = NORMAL;
	m_tCount[GUIDED] = 200;

	m_bCheck = true;
	m_bEvade = false;
	m_bView = true;
	m_strDrawID = "Player1";
	m_iSound = 3;
	m_iLife = 3;
}

int CPlayer::Progress()
{
	if (m_bPlay)
	{
		KeyCheck();
		if (m_dwLifeTime + 1000 < GetTickCount())
		{
			m_bEvade = false;
			m_bView = true;
		}
	}
	else
	{
		if (m_dwLifeTime + 2000 < GetTickCount())
		{
			m_dwLifeTime = GetTickCount();
			m_bPlay = true;
		}
		m_tInfo.fy -= 1.5f;
	}
	Frame();
	Direction();
	Motion();
	if (m_iLife == -1)
	{
		m_bPlay = false;
		m_bEvade = true;
		m_bView = true;
		m_tInfo.fy += 1.5f;
	}

	return 0;
}

void CPlayer::Render(HDC hdc)
{
	if (m_bEvade)
	{
		if (m_dwViewTime + 200 < GetTickCount())
		{
			m_dwViewTime = GetTickCount();
			m_bView = (m_bView) ? false : true;
		}
	}
	if (m_bView)
	{
		TransparentBlt(hdc,
			int((m_tInfo.fx - m_BmpInfo.fcx / 2)),
			int((m_tInfo.fy - m_BmpInfo.fcy / 2)),
			(int)m_BmpInfo.fcx, (int)m_BmpInfo.fcy,
			(*m_pMapBmp)[m_strDrawID]->GetMemDC(),
			(int)(m_BmpInfo.fx + 32 * m_tFrame.iStart), 
			(int)(m_BmpInfo.fy + 48 * m_tFrame.iScene), 
			(int)m_BmpInfo.fcx, (int)m_BmpInfo.fcy,
			RGB(255, 255, 255));
		TransparentBlt(hdc,
			int((m_tInfo.fx - 4)),
			int((m_tInfo.fy - 4)),
			8, 8,
			(*m_pMapBmp)["Player1"]->GetMemDC(),
			(int)(128 + 8 * m_tFrame.iStart), 0,
			8, 8,
			RGB(255, 255, 255));
	}
	for (int i = 0; i < m_iLife; ++i)
	{
		StretchBlt(hdc,
			10 + i*35, WINCY - 30,
			20, 20,
			(*m_pMapBmp)["Bullet"]->GetMemDC(),
			350, 64,
			16, 16,
			SRCCOPY);
	}
}

void CPlayer::Release()
{
}

int CPlayer::Hit()
{
	m_dwLifeTime = GetTickCount();
	m_bPlay = false;
	m_bEvade = true;
	m_dwViewTime = GetTickCount();
	m_dwKey = NULL;

	if (m_iLife > 0)
	{
		m_iLife--;
		m_tInfo.fx = WINCX / 2;
		m_tInfo.fy = WINCY + 100;
	}
	else
	{
		m_iLife--;
		return 1;
	}

	return 0;
}

void CPlayer::KeyCheck()
{
	m_dwKey = GET_SINGLE(CKeyMgr)->GetKey();

	if (m_dwKey & KEY_UP && m_tInfo.fy > m_tInfo.fcy / 2)
	{
		m_tInfo.fy -= m_fSpeed;
	}
	if (m_dwKey & KEY_DOWN && m_tInfo.fy < WINCY - m_tInfo.fcy / 2)
	{
		m_tInfo.fy += m_fSpeed;
	}
	if (m_dwKey & KEY_LEFT && m_tInfo.fx > m_tInfo.fcx / 2 - m_ptScroll.x)
	{
		m_tInfo.fx -= m_fSpeed;
	}
	if (m_dwKey & KEY_RIGHT && m_tInfo.fx < WINCX - m_tInfo.fcx / 2 - m_ptScroll.x)
	{
		m_tInfo.fx += m_fSpeed;
	}
	if (m_dwKey & KEY_SPACE)
	{
		if (m_dwShoot + m_tCount[m_iSkillNum] < GetTickCount())
		{
			m_dwShoot = GetTickCount();
			GET_SINGLE(CDevice)->SoundPlay(m_iSound, 0);
			SkillShot(m_iSkillNum);
		}
		
	}
	if (GetAsyncKeyState('Z'))
	{
		m_iBSprd = 1.f;
		m_fSpeed = 2.f;
	}
	else
	{
		m_fSpeed = 5.f;
		m_iBSprd = 7.5f;
	}
	if (GetAsyncKeyState('A'))
	{
		m_iSkillNum = NORMAL;
		m_strDrawID = "Player1";
		m_iSound = 3;
	}
	if (GetAsyncKeyState('S'))
	{
		m_iSkillNum = SPREAD;
		m_strDrawID = "Player2";
		GET_SINGLE(CDevice)->SoundStop(3);
		m_iSound = 2;
	}
	if (GetAsyncKeyState('D'))
	{
		m_iSkillNum = GUIDED;
		m_strDrawID = "Player3";
		m_iSound = 3;
	}
	if (GetAsyncKeyState('C'))
	{
		if (m_bEvade)
		{
			m_bEvade = false;
			m_bView = true;
		}
		else
		{
			m_bEvade = true;
			m_dwViewTime = GetTickCount();
		}
	}
}

void CPlayer::Frame()
{
	if (m_dwTime + m_tFrame.dwTime < GetTickCount())
	{
		m_dwTime = GetTickCount();
		++m_tFrame.iStart;

		if (m_tFrame.iStart >= m_tFrame.iLast)
		{
			if (m_dwState & STATE_STAND)
				m_tFrame.iStart = 0;
			else
				m_tFrame.iStart = 3;

			if (m_dwState != STATE_STAND)
				m_dwState = STATE_STAND;
		}
	}
}

void CPlayer::Direction()
{
	if (!(KEY_RIGHT & KEY_LEFT & m_dwKey))
		m_dwState = STATE_STAND;

	if (KEY_LEFT & m_dwKey)
		m_dwState = STATE_WALKL;

	if (KEY_RIGHT & m_dwKey)
		m_dwState = STATE_WALKR;
}

void CPlayer::Motion()
{
	if (m_dwState & STATE_STAND)
		SetScene(4, 0, 100);

	if (m_dwState & STATE_WALKL)
		SetScene(7, 1, 100);

	if (m_dwState & STATE_WALKR)
		SetScene(7, 2, 100);
}

void CPlayer::SetScene(int _last, int _scene, DWORD _time)
{
	if (m_tFrame.iScene != _scene)
		m_tFrame.iStart = 0;

	m_tFrame.iLast = _last;
	m_tFrame.iScene = _scene;
	m_tFrame.dwTime = _time;
}

void CPlayer::SkillShot(SKILLID _id)
{
	switch (_id)
	{
	case NORMAL:
	{
		CreateBullet<CNormalBullet>(0, -20, m_fAngle, PBL_NORMAL, 0);
		CreateBullet<CNormalBullet>(7, -15, m_fAngle - m_iBSprd, PBL_NORMAL, 0);
		CreateBullet<CNormalBullet>(-7, -15, m_fAngle + m_iBSprd, PBL_NORMAL, 0);
		break;
	}
	case SPREAD:
	{
		CreateBullet<CNormalBullet>(0, -20, m_fAngle, PBL_NORMAL, 1);
		CreateBullet<CNormalBullet>(3, -18, m_fAngle - m_iBSprd * 1.3f, PBL_NORMAL, 1);
		CreateBullet<CNormalBullet>(-3, -18, m_fAngle + m_iBSprd * 1.3f, PBL_NORMAL, 1);
		CreateBullet<CNormalBullet>(7, -15, m_fAngle - m_iBSprd * 2.8f, PBL_NORMAL, 1);
		CreateBullet<CNormalBullet>(-7, -15, m_fAngle + m_iBSprd * 2.8f, PBL_NORMAL, 1);
		CreateBullet<CNormalBullet>(10, -13, m_fAngle - m_iBSprd * 4.5f, PBL_NORMAL, 1);
		CreateBullet<CNormalBullet>(-10, -13, m_fAngle + m_iBSprd * 4.5f, PBL_NORMAL, 1);
		CreateBullet<CNormalBullet>(10, -13, m_fAngle - m_iBSprd * 7, PBL_NORMAL, 1);
		CreateBullet<CNormalBullet>(-10, -13, m_fAngle + m_iBSprd * 7, PBL_NORMAL, 1);
		break;
	}
	case GUIDED:
	{
		CreateBullet<CBounceBullet>(3, 3, 45, PBL_BOUNCE);
		CreateBullet<CBounceBullet>(-3, 3, 135, PBL_BOUNCE);
		CreateBullet<CBounceBullet>(1, 5, 60, PBL_BOUNCE);
		CreateBullet<CBounceBullet>(-1, 5, 120, PBL_BOUNCE);
		CreateBullet<CGuideBullet>(5, 0, 30, PBL_GUIDE, 0);
		CreateBullet<CGuideBullet>(-5, 0, 150, PBL_GUIDE, 0);
		break;
	}
	case SKL_A:
		break;
	case SKL_B:
		break;
	case SKL_C:
		break;
	case SKL_END:
		break;
	default:
		break;
	}
}

template<typename T>
void CPlayer::CreateBullet(float _x, float _y, float _angle, OBJTYPE _type, int _typenum)
{
	_x += m_tInfo.fx;
	_y += m_tInfo.fy;

	map<OBJTYPE, list<CObj*>>::iterator iter = m_pBulletList->find(_type);
	if (iter == m_pBulletList->end())
	{
		CBridge*	pBridge = new T;
		pBridge->SetAngle(_angle);
		((CBullet_Bridge*)pBridge)->SetType(_typenum);

		CObj* pBullet = CObjFactory<CBullet>::CreateObj(_x, _y, pBridge);
		pBullet->m_bCheck = true;

		list<CObj*> ObjList;
		ObjList.push_back(pBullet);
		m_pBulletList->insert(make_pair(_type, ObjList));
	}
	else
	{
		for (list<CObj*>::iterator Bullet = iter->second.begin(); Bullet != iter->second.end(); ++Bullet)
		{
			if (!(*Bullet)->m_bCheck)
			{
				(*Bullet)->SetPos(_x, _y);
				((CBullet_Bridge*)(((CBullet*)*Bullet)->GetBridge()))->SetType(_typenum);
				(((CBullet*)*Bullet)->GetBridge())->SetAngle(_angle);
				((CGuideBullet*)(((CBullet*)*Bullet)->GetBridge()))->SetTarget(NULL);
				(*Bullet)->Initialize();
				(*Bullet)->m_bCheck = true;
				return;
			}
		}
		CBridge*	pBridge = new T;
		pBridge->SetAngle(_angle);
		((CBullet_Bridge*)pBridge)->SetType(_typenum);

		CObj* pBullet = CObjFactory<CBullet>::CreateObj(_x, _y, pBridge);
		pBullet->m_bCheck = true;

		iter->second.push_back(pBullet);
	}
}