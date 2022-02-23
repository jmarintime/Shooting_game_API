#pragma once
#include "SceneObj.h"

class CLogo : public CSceneObj
{
private:
	HWND	m_hVideo;

public:
	virtual void Initialize();
	virtual int Progress();
	virtual void Render(HDC hdc);
	virtual void Release();
public:
	CLogo();
	virtual ~CLogo();
};

