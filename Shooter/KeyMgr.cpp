#include "stdafx.h"
#include "KeyMgr.h"


CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::CheckKey()
{
	m_dwKey = 0;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_dwKey |= KEY_UP;

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_dwKey |= KEY_DOWN;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_dwKey |= KEY_LEFT;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_dwKey |= KEY_RIGHT;

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_dwKey |= KEY_ENTER;

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		m_dwKey |= KEY_ESC;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_dwKey |= KEY_SPACE;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_dwKey |= KEY_LBUTTON;

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_dwKey |= KEY_RBUTTON;
}
