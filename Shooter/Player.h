#pragma once
#include "Obj.h"

class CPlayer : public CObj
{
private:
	string		m_strDrawID;
	float		m_fSpeed;
	float		m_fAngle;
	DWORD		m_dwKey;
	DWORD		m_dwTime;
	DWORD		m_dwShoot;
	DWORD		m_dwState;
	bool		m_bView;

	FRAME		m_tFrame;
	DWORD		m_tCount[SKL_END];
	SKILLID		m_iSkillNum;

	INFO		m_BmpInfo;

	map<OBJTYPE,list<CObj*>>*	m_pBulletList;

	float		m_iBSprd;
	int			m_iSound;
	int			m_iLife;
	bool		m_bPlay;
	DWORD		m_dwLifeTime;
	DWORD		m_dwViewTime;
public:
	float	GetSpeed() const { return m_fSpeed; }
	void	SetBullet(map<OBJTYPE, list<CObj*>>* _list) { m_pBulletList = _list; }

	int Hit();

private:
	void KeyCheck();
	void Frame();
	void Direction();
	void Motion();
	void SetScene(int _last, int _scene, DWORD _time);
	template <typename T>
	void CreateBullet(float _x, float _y, float _angle, OBJTYPE _type, int _typenum = 5);
	void SkillShot(SKILLID _id);
public:
	virtual void Initialize();
	virtual int Progress();
	virtual void Render(HDC hdc);
	virtual void Release();
public:
	CPlayer();
	~CPlayer();
};
