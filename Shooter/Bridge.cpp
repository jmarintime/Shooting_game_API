#include "stdafx.h"
#include "Bridge.h"

#include "resource.h"

CBridge::CBridge()
{
}


CBridge::~CBridge()
{
}

void CBridge::RenderBlt(string _string, INFO _info, INFO _bmpinfo)
{
	//SetStretchBltMode((*m_pMapBmp)[BackBuffer]->GetMemDC(), HALFTONE);
	StretchBlt((*m_pMapBmp)["BackBlack"]->GetMemDC(),
		(int)(_info.fx - _info.fcx / 2), (int)(_info.fy - _info.fcy / 2),
		(int)_info.fcx, (int)_info.fcy,
		(*m_pMapBmp)[_string]->GetMemDC(),
		int(_bmpinfo.fx),
		int(_bmpinfo.fy),
		(int)(_bmpinfo.fcx), (int)(_bmpinfo.fcy),
		SRCCOPY);
}

void CBridge::ReverseBlt(string _string, INFO _info, INFO _bmpinfo)
{
	//SetStretchBltMode((*m_pMapBmp)[BackBuffer]->GetMemDC(), HALFTONE);
	StretchBlt((*m_pMapBmp)["BackBlack"]->GetMemDC(),
		(int)(_info.fx + _info.fcx / 2), (int)(_info.fy - _info.fcy / 2),
		-(int)_info.fcx, (int)_info.fcy,
		(*m_pMapBmp)[_string]->GetMemDC(),
		int(_bmpinfo.fx),
		int(_bmpinfo.fy),
		(int)(_bmpinfo.fcx + _bmpinfo.fx), (int)(_bmpinfo.fcy + _bmpinfo.fy),
		SRCCOPY);
}

void CBridge::RotateBlt(string _string, INFO _info, INFO _bmpinfo, float _angle)
{
	POINT PTemp[4];
	PTemp[0] = { (LONG)(_info.fx - _info.fcx / 2), (LONG)(_info.fy - _info.fcy / 2) };
	PTemp[1] = { (LONG)(_info.fx + _info.fcx / 2), (LONG)(_info.fy - _info.fcy / 2) };
	PTemp[2] = { (LONG)(_info.fx - _info.fcx / 2), (LONG)(_info.fy + _info.fcy / 2) };

	RECT TempRC = { 0, 0, 0, 0 };
	for (int i = 0; i < 3; i++)
	{
		PTemp[i].x -= _info.fx;
		PTemp[i].y -= _info.fy;

		POINT temp;
		temp.x = PTemp[i].x * cosf(_angle * PI / 180) + PTemp[i].y * sinf(_angle * PI / 180);
		temp.y = - PTemp[i].x * sinf(_angle * PI / 180) + PTemp[i].y * cosf(_angle * PI / 180);

		PTemp[i].x = temp.x + _info.fx;
		PTemp[i].y = temp.y + _info.fy;
	}

	PlgBlt((*m_pMapBmp)["BackBlack"]->GetMemDC(),
		PTemp, 
		(*m_pMapBmp)[_string]->GetMemDC(),
		int(_bmpinfo.fx),
		int(_bmpinfo.fy),
		(int)(_bmpinfo.fcx), (int)(_bmpinfo.fcy),
		NULL, NULL, NULL);
}

