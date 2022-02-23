#pragma once
#include "Include.h"

class CObj;
class CObjMgr
{
private:
	multimap<int, CObj*>	m_MapObj;

public:
	void AddRenderObj(CObj* pObj);
	void Render(HDC hdc);
	void Clear();

public:
	DECLARE_SINGETON(CObjMgr);

private:
	CObjMgr();
public:
	~CObjMgr();
};

