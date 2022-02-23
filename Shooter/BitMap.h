#pragma once

#include "Include.h"

class CBitMap
{
public:
	HDC			m_hdc, m_MemDC;
	HBITMAP		m_bitMap, m_oldbitMap;

public:
	HDC	GetMemDC() { return m_MemDC; }

	CBitMap* LoadBmp(PTCHAR pFileName);
	CBitMap* LoadBmp(int ResourceName);
	void	Release();
public:
	CBitMap();
	~CBitMap();
};

