#include "stdafx.h"
#include "Obj.h"

map<string, CBitMap*>* CObj::m_pMapBmp = NULL;

POINT CObj::m_ptScroll = { 0 };

RECT CObj::GetRect()
{
	RECT rt = {
		int(m_tInfo.fx - m_tInfo.fcx / 2.f),
		int(m_tInfo.fy - m_tInfo.fcy / 2.f),
		int(m_tInfo.fx + m_tInfo.fcx / 2.f),
		int(m_tInfo.fy + m_tInfo.fcy / 2.f)
	};

	return rt;
}

POINT CObj::GetPoint()
{
	POINT pt;

	pt.x = m_tInfo.fx;
	pt.y = m_tInfo.fy;

	return pt;
}

void CObj::SetPos(float _fx, float _fy)
{
	m_tInfo.fx = _fx;
	m_tInfo.fy = _fy;
}

CObj::CObj()
{
}


CObj::~CObj()
{
}
