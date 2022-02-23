#include "stdafx.h"
#include "Monster_Bridge.h"

CMonster_Bridge::CMonster_Bridge()
{
}


CMonster_Bridge::~CMonster_Bridge()
{
}

void CMonster_Bridge::CopyBullet(CObj * _obj)
{
	INFO temp = _obj->GetInfo();
	map<OBJTYPE, list<CObj*>>::iterator iter = m_pBulletList->find(ABL_COPY);
	if (iter == m_pBulletList->end())
	{
		CBridge*	pBridge = ((CBullet*)_obj)->GetBridge()->Clone();

		CObj* pBullet = CObjFactory<CBullet>::CreateObj(temp.fx, WINCY + 20, pBridge);
		pBullet->m_bCheck = true;

		list<CObj*> ObjList;
		ObjList.push_back(pBullet);
		m_pBulletList->insert(make_pair(ABL_COPY, ObjList));
	}
	else
	{
		for (list<CObj*>::iterator Bullet = iter->second.begin(); Bullet != iter->second.end(); ++Bullet)
		{
			if (!(*Bullet)->m_bCheck)
			{
				(*Bullet)->m_bCheck = true;
				(*Bullet)->SetPos(temp.fx, WINCY + 20);
				(*Bullet)->Initialize();
				(((CBullet*)*Bullet)->GetBridge())->SetAngle(((CBullet*)_obj)->GetBridge()->GetAngle());
				return;
			}
		}
		CBridge*	pBridge = ((CBullet*)_obj)->GetBridge()->Clone();

		CObj* pBullet = CObjFactory<CBullet>::CreateObj(temp.fx, WINCY + 20, pBridge);

		iter->second.push_back(pBullet);
	}
}
