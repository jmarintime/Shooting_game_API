#pragma once
#include "Obj.h"

class CStageBack : public CObj
{
private:
	CObj*	m_pPlayer;
	POINT	m_ptOffset;
	SCROLL	m_Scroll;

public:
	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }
	void StageScroll();

public:
	virtual void Initialize();
	virtual int Progress();
	virtual void Render(HDC hdc);
	virtual void Release();
public:
	CStageBack();
	~CStageBack();
};

