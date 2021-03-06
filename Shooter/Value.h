#pragma once

const int WINCX = 600;
const int WINCY = 850;

const float	PI = 3.141592f;

extern HWND g_hWnd;
extern HINSTANCE hInst;

const DWORD		STATE_STAND	= 0x00000001;
const DWORD		STATE_WALKL	= 0x00000002;
const DWORD		STATE_WALKR = 0x00000004;
const DWORD		STATE_HIT	= 0x00000008;
const DWORD		STATE_DIE	= 0x00000010;

const DWORD		KEY_UP		= 0x00000001;
const DWORD		KEY_DOWN	= 0x00000002;
const DWORD		KEY_LEFT	= 0x00000004;
const DWORD		KEY_RIGHT	= 0x00000008;
const DWORD		KEY_SPACE	= 0x00000010;
const DWORD		KEY_ENTER	= 0x00000020;
const DWORD		KEY_ESC		= 0x00000040;
const DWORD		KEY_LBUTTON = 0x00000080;
const DWORD		KEY_RBUTTON = 0x00000100;
