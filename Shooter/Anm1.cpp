#include "stdafx.h"
#include "Anm1.h"

CAnm1::CAnm1()
{
}


CAnm1::~CAnm1()
{
}

void CAnm1::Pattern()
{
	switch (m_iPhase)
	{
	case 0:
		m_fAngle -= 0.3f;
		break;
	case 1:
		m_fAngle += 0.3f;
		break;
	case 2:
		m_fAngle -= 0.4f;
		break;
	case 3:
		m_fAngle += 0.4f;
		break;
	default:
		break;
	}
}

void CAnm1::Initialize()
{
	switch (m_iPhase)
	{
	case 0:
		m_fAngle = 230.f;
		break;
	case 1:
		m_fAngle = 310.f;
		break;
	case 2:
		m_fAngle = 260.f;
		break;
	case 3:
		m_fAngle = 280.f;
		break;
	default:
		break;
	}
	m_pMapBmp = m_pObj->GetBitMap();
	m_tStat = STAT(20);
	INFO tinfo = m_pObj->GetInfo();
	tinfo.fcx = 50;
	tinfo.fcy = 50;

	m_pObj->SetInfo(tinfo);
	m_dwTime = GetTickCount();
	m_dwCoolTime = rand() % 3 * 250 + 1250;

	m_BmpInfo = INFO(6, 11, 50, 50);

	m_fSpeed = 3.f;
}

int CAnm1::Progress(INFO& rInfo)
{
	Pattern();

	rInfo.fx += cosf(m_fAngle * PI / 180) * m_fSpeed;
	rInfo.fy -= sinf(m_fAngle * PI / 180) * m_fSpeed;

	if (rInfo.fx < -200 || rInfo.fx > WINCX + 200 || rInfo.fy < -200 || rInfo.fy > WINCY + 200)
		return 삭제;

	if (m_tStat.iHP <= 0)
		return 삭제;

	if (m_dwTime + m_dwCoolTime < GetTickCount())
	{
		m_dwTime = GetTickCount();
		m_dwCoolTime = rand() % 3 * 250 + 1250;
		float TargetAngle = CMathMgr::GetAngle(m_pTarget, m_pObj);
		Shoot(TargetAngle);
	}

	return 0;
}

void CAnm1::Render(HDC hdc)
{
	INFO tinfo = m_pObj->GetInfo();
	TransparentBlt(hdc,
		int((tinfo.fx - tinfo.fcx / 2)),
		int((tinfo.fy - tinfo.fcy / 2)),
		(int)tinfo.fcx, (int)tinfo.fcy,
		(*m_pMapBmp)["Monster"]->GetMemDC(),
		(int)(m_BmpInfo.fx),
		(int)(m_BmpInfo.fy),
		(int)tinfo.fcx, (int)tinfo.fcy,
		RGB(255, 255, 255));
}

void CAnm1::Release()
{
}

void CAnm1::Shoot(float _angle)
{
	INFO tinfo = m_pObj->GetInfo();
	CreateBullet<CNormalBulletA>(tinfo.fx, tinfo.fy, _angle + rand()%7 - 3, ABL_NORMAL, 0, 3.5f);
}
