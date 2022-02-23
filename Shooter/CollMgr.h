#pragma once
#include "Include.h"

class CObj;
class CCollMgr
{
public:
	static bool Collrect(CObj* pTemp, CObj* pDest);
	static bool Collcircle(CObj* pTemp, CObj* pDest);
	static bool CollRcCir(CObj* pTemp, CObj* pDest);

public:
	CCollMgr();
	~CCollMgr();
};

