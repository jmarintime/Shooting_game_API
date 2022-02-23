#pragma once
#include "Bridge.h"

#include "ObjFactory.h"
#include "MathMgr.h"
#include "Stage.h"

#include "Bullet.h"
#include "NormalBulletA.h"
#include "ThrustBulletA.h"
#include "ReverseBullet.h"
#include "BounceBullet.h"

class CMonster_Bridge : public CBridge
{
protected:
	int		m_iPhase;
	DWORD	m_dwCoolTime;

	CObj*			m_pTarget;
	map<OBJTYPE, list<CObj*>>*	m_pBulletList;

public:
	void	SetPhase(int _phase) { m_iPhase = _phase; }
	void	SetBullet(map<OBJTYPE, list<CObj*>>* _list) { m_pBulletList = _list; }
	void	SetTarget(CObj* _target) { m_pTarget = _target; }

protected:
	template <typename T>
	void CreateBullet(float _x, float _y, float _angle, OBJTYPE _type, int _time = 0, float _speed = 0.f, int _typenum = 0);
	void CopyBullet(CObj* _obj);

public:
	virtual void Initialize()PURE;
	virtual int Progress(INFO& rInfo)PURE;
	virtual void Render(HDC hdc)PURE;
	virtual void Release()PURE;
	virtual CBridge* Clone()PURE;

public:
	CMonster_Bridge();
	virtual ~CMonster_Bridge();
};

template<typename T>
void CMonster_Bridge::CreateBullet(float _x, float _y, float _angle, OBJTYPE _type, int _time, float _speed, int _typenum)
{
	map<OBJTYPE, list<CObj*>>::iterator iter = m_pBulletList->find(_type);
	if (iter == m_pBulletList->end())
	{
		CBridge*	pBridge = new T;
		pBridge->SetAngle(_angle);
		((CBullet_Bridge*)pBridge)->SetType(_typenum);

		CObj* pBullet = CObjFactory<CBullet>::CreateObj(_x, _y, pBridge);
		pBullet->m_bCheck = true;
		if (_speed != 0.f)
			((CBullet_Bridge*)(((CBullet*)pBullet)->GetBridge()))->SetSpeed(_speed);
		if (_type == ABL_THRUST)
		{
			((CThrustBulletA*)(((CBullet*)pBullet)->GetBridge()))->SetTarget(m_pTarget);
			((CThrustBulletA*)(((CBullet*)pBullet)->GetBridge()))->SetTime(_time);
		}

		list<CObj*> ObjList;
		ObjList.push_back(pBullet);
		m_pBulletList->insert(make_pair(_type, ObjList));
	}
	else
	{
		for (list<CObj*>::iterator Bullet = iter->second.begin(); Bullet != iter->second.end(); ++Bullet)
		{
			if (!(*Bullet)->m_bCheck)
			{
				(*Bullet)->m_bCheck = true;
				(*Bullet)->SetPos(_x, _y);
				((CBullet_Bridge*)(((CBullet*)*Bullet)->GetBridge()))->SetType(_typenum);
				(*Bullet)->Initialize();
				(((CBullet*)*Bullet)->GetBridge())->SetAngle(_angle);
				if (_speed != 0.f)
					((CBullet_Bridge*)(((CBullet*)*Bullet)->GetBridge()))->SetSpeed(_speed);
				if (_type == ABL_THRUST)
				{
					((CThrustBulletA*)(((CBullet*)*Bullet)->GetBridge()))->SetTime(_time);
				}
				return;
			}
		}
		CBridge*	pBridge = new T;
		pBridge->SetAngle(_angle);
		((CBullet_Bridge*)pBridge)->SetType(_typenum);

		CObj* pBullet = CObjFactory<CBullet>::CreateObj(_x, _y, pBridge);
		pBullet->m_bCheck = true;
		if (_speed != 0.f)
			((CBullet_Bridge*)(((CBullet*)pBullet)->GetBridge()))->SetSpeed(_speed);
		if (_type == ABL_THRUST)
		{
			((CThrustBulletA*)(((CBullet*)pBullet)->GetBridge()))->SetTarget(m_pTarget);
			((CThrustBulletA*)(((CBullet*)pBullet)->GetBridge()))->SetTime(_time);
		}

		iter->second.push_back(pBullet);
	}
}
