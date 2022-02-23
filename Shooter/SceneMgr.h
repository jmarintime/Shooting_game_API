#pragma once
#include "Include.h"

class CSceneObj;
class CSceneMgr
{
private:
	CSceneObj*	m_pScene;

public:
	void SetScene(SCENEID _scene);
	void Progress();
	void Render(HDC hdc);
	void Release();

public:
	DECLARE_SINGETON(CSceneMgr);

private:
	CSceneMgr();
public:
	~CSceneMgr();
};

