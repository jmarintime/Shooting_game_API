#pragma once
#include "Value.h"

class CMouse
{
public:
	static POINT GetPos()
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		return pt;
	}
public:
	CMouse();
	~CMouse();
};

