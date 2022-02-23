#pragma once
#include "Value.h"

class CMainGame
{
private:
	HDC m_hdc;
public:
	void Initialize();
	void Progress();
	void Render();
	void Release();

public:
	CMainGame();
	~CMainGame();
};

