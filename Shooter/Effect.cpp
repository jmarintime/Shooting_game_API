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

	if (iPro == ����)
		return ����;

	if (iPro == Ŭ����)
		return Ŭ����;

	if (iPro == ����)
		return ����;

	if (iPro == ��Ȱ��)
		return ��Ȱ��;

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