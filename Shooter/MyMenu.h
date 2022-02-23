#pragma once
#include "SceneObj.h"

class CObj;
class CMyMenu : public CSceneObj
{
private:
	CObj*			m_pBackGround;
	list<CObj*>		m_ButtonList;

public:
	CObj* CreateButton(float _fx, float _fy, string _drowid);
public:
	virtual void Initialize();
	virtual int Progress();
	virtual void Render(HDC hdc);
	virtual void Release();
public:
	CMyMenu();
	virtual ~CMyMenu();
};

