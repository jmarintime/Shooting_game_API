#include "stdafx.h"
#include "Monster.h"

#include "Monster_Bridge.h"

CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Hit(int _damage)
{
	if (m_bCheck)
	{
		m_pBridge->m_tStat.iHP -= _damage;
	}
}

void CMonster::Initialize()
{
	m_tInfo.iLayer = 1;
	m_bEvade = false;

	if (m_pBridge)
		m_pBridge->Initialize();
}

int CMonster::Progress()
{
	int iPro = m_pBridge->Progress(m_tInfo);

	if (iPro == 삭제)
		return 삭제;

	if (iPro == 클리어)
		return 클리어;

	if (iPro == 정리)
		return 정리;

	if (iPro == 비활성)
		return 비활성;

	return 0;
}

void CMonster::Render(HDC hdc)
{
	if (m_pBridge)
		m_pBridge->Render(hdc);
}

void CMonster::Release()
{
	Safe_Delete(m_pBridge);
}