#pragma once
#include "SceneObj.h"

class CObj;
class CStage : public CSceneObj
{
private:
	CObj*						m_pBackGround;
	list<CObj*>					m_ObjList[OBJ_END];
	map<OBJTYPE, list<CObj*>>	m_BulletList[BUL_END];

private:
	void	BulletClear();
	void	CreateBullet();

public:
	virtual void Initialize();
	virtual int Progress();
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	CStage();
	virtual ~CStage();
};

