#include "stdafx.h"
#include "Bullet.h"

#include "Bridge.h"

CBullet::CBullet()
	:m_pBridge(NULL)
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.iLayer = 4;

	if (m_pBridge)
		m_pBridge->Initialize();
}

int CBullet::Progress()
{
	int iPro = m_pBridge->Progress(m_tInfo);

	if (iPro == 삭제)
		return 삭제;
	else if (iPro == 비활성)
		m_bCheck = false;

	return 0;
}

void CBullet::Render(HDC hdc)
{
	if (m_pBridge)
		m_pBridge->Render(hdc);
}

void CBullet::Release()
{
	Safe_Delete(m_pBridge);
}