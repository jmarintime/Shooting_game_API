#include "stdafx.h"
#include "BitMap.h"

#include "resource.h"

CBitMap::CBitMap()
{
}


CBitMap::~CBitMap()
{
	Release();
}

CBitMap * CBitMap::LoadBmp(PTCHAR pFileName)
{
	m_hdc = GetDC(g_hWnd);
	m_MemDC = CreateCompatibleDC(m_hdc);	//�̹��� ������ �����ϱ����� ��

	m_bitMap = (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//m_bitMap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));

	if (!m_bitMap)
	{
		MessageBox(g_hWnd, pFileName, L"File Load False", NULL);
	}
	// SelectObject�Լ��� ����� : m_MemDC�� m_bitmap�� ������ ���� �ִ� ���� �����Ѵ�.
	m_oldbitMap = (HBITMAP)SelectObject(m_MemDC, m_bitMap);

	ReleaseDC(g_hWnd, m_hdc);

	return this;
}

CBitMap * CBitMap::LoadBmp(int ResourceName)
{
	m_hdc = GetDC(g_hWnd);
	m_MemDC = CreateCompatibleDC(m_hdc);	//�̹��� ������ �����ϱ����� ��

	m_bitMap = LoadBitmap(hInst, MAKEINTRESOURCE(ResourceName));

	if (!m_bitMap)
	{
		MessageBox(g_hWnd, L"pFileName", L"File Load False", NULL);
	}
	// SelectObject�Լ��� ����� : m_MemDC�� m_bitmap�� ������ ���� �ִ� ���� �����Ѵ�.
	m_oldbitMap = (HBITMAP)SelectObject(m_MemDC, m_bitMap);

	ReleaseDC(g_hWnd, m_hdc);

	/*StretchBlt(m_MemDC,
		0, 0,
		300, 300,
		m_MemDC,
		10,
		5,
		300, 300,
		SRCCOPY);*/

	return this;
}

void CBitMap::Release()
{
	SelectObject(m_MemDC, m_oldbitMap);
	DeleteObject(m_bitMap);
	DeleteObject(m_oldbitMap);
	DeleteDC(m_MemDC);
}