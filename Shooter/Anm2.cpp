#include "stdafx.h"
#include "Anm2.h"


CAnm2::CAnm2()
{
}


CAnm2::~CAnm2()
{
}

void CAnm2::Pattern()
{
	INFO tinfo = m_pObj->GetInfo();
	switch (m_iPhase)
	{
	case 0:
		m_fSpeed = 1.f;
		break;
	case 1:
		m_fSpeed = 0.f;
		if (m_dwTime + 5000 < GetTickCount())
		{
			m_iPhase = 2;
		}
		break;
	case 2:
		m_fSpeed = 1.f;
		if (tinfo.fx > WINCX / 2)
		{
			m_fAngle = 60.f;
		}
		else
		{
			m_fAngle = 120.f;
		}
		m_dwCoolTime = GetTickCount() + 10000;
		break;
	default:
		break;
	}
}

void CAnm2::Initialize()
{
	m_pMapBmp = m_pObj->GetBitMap();
	m_tStat = STAT(600);
	INFO tinfo = m_pObj->GetInfo();
	tinfo.fcx = 140;
	tinfo.fcy = 128;

	m_pObj->SetInfo(tinfo);
	m_dwTime = GetTickCount();
	m_dwCoolTime = GetTickCount() + 3000;

	m_fSpeed = 1.f;
	m_fAngle = 270.f;
}

int CAnm2::Progress(INFO& rInfo)
{
	Pattern();

	rInfo.fx += cosf(m_fAngle * PI / 180) * m_fSpeed;
	rInfo.fy -= sinf(m_fAngle * PI / 180) * m_fSpeed;

	if (rInfo.fx < -200 || rInfo.fx > WINCX + 200 || rInfo.fy < -200 || rInfo.fy > WINCY + 200)
		return 삭제;

	if (m_tStat.iHP <= 0)
		return 삭제;

	if (m_dwCoolTime < GetTickCount())
	{
		m_dwCoolTime += rand() % 3 * 250 + 2500;
		float TargetAngle = CMathMgr::GetAngle(m_pTarget, m_pObj) + rand() % 7 - 3;
		for (int i = -30; i <= 30; i += 10)
		{
			ShootSpeed(TargetAngle + i, 2.0f);
			ShootSpeed(TargetAngle + i, 2.3f);
			ShootSpeed(TargetAngle + i, 2.6f);
			ShootSpeed(TargetAngle + i, 2.9f);
			ShootSpeed(TargetAngle + i, 3.2f);
		}
		Shoot(-50, 0, 225);
		Shoot(50, 0, 315);
	}
	if (rInfo.fy > WINCY / 3 && m_iPhase == 0)
	{
		m_iPhase = 1;
		m_dwTime = GetTickCount();
	}
		

	return 0;
}

void CAnm2::Render(HDC hdc)
{
	INFO tinfo = m_pObj->GetInfo();
	TransparentBlt(hdc,
		int((tinfo.fx - tinfo.fcx / 2)),
		int((tinfo.fy - tinfo.fcy / 2)),
		(int)tinfo.fcx, (int)tinfo.fcy,
		(*m_pMapBmp)["Monster2"]->GetMemDC(),
		0, 0,
		(int)tinfo.fcx, (int)tinfo.fcy,
		RGB(255, 255, 255));
}

void CAnm2::Release()
{
}

void CAnm2::Shoot(float _angle)
{
	INFO tinfo = m_pObj->GetInfo();
	CreateBullet<CNormalBulletA>(tinfo.fx, tinfo.fy, _angle, ABL_NORMAL);
}

void CAnm2::ShootSpeed(float _angle, float _speed)
{
	INFO tinfo = m_pObj->GetInfo();
	CreateBullet<CNormalBulletA>(tinfo.fx, tinfo.fy, _angle, ABL_NORMAL, 0, _speed, 2);
}

void CAnm2::Shoot(float _x, float _y)
{
	INFO tinfo = m_pObj->GetInfo();
	tinfo.fx += _x;
	tinfo.fy += _y;
	float TargetAngle = CMathMgr::GetAngle(m_pTarget, tinfo) + rand() % 7 - 3;
	CreateBullet<CNormalBulletA>(tinfo.fx, tinfo.fy, TargetAngle, ABL_NORMAL, 0, 3.5f);
}

void CAnm2::Shoot(float _x, float _y, float _angle)
{
	INFO tinfo = m_pObj->GetInfo();
	tinfo.fx += _x;
	tinfo.fy += _y;
	CreateBullet<CBounceBullet>(tinfo.fx, tinfo.fy, _angle, ABL_BOUNCE);
}