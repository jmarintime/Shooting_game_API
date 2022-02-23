#include "stdafx.h"
#include "Effect.h"

#include "Effect_Bridge.h"

CEffect::CEffect()
{
}


CEffect::~CEffect()
{
	Release();
}

void CEffect::Initialize()
{
	m_tInfo.iLayer = 3;
	m_bEvade = false;

	if (m_pBridge)
		m_pBridge->Initialize();
}

int CEffect::Progress()
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

void CEffect::Render(HDC hdc)
{
	if (m_pBridge)
		m_pBridge->Render(hdc);
}

void CEffect::Release()
{
	Safe_Delete(m_pBridge);
}