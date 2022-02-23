#include "stdafx.h"
#include "ObjMgr.h"

#include "Obj.h"

void CObjMgr::AddRenderObj(CObj * pObj)
{
	m_MapObj.insert(make_pair(pObj->GetInfo().iLayer, pObj));
}

void CObjMgr::Render(HDC hdc)
{
	for (multimap<int, CObj*>::iterator iter = m_MapObj.begin(); iter != m_MapObj.end(); ++iter)
	{
		iter->second->Render(hdc);
	}
}

void CObjMgr::Clear()
{
	m_MapObj.clear();
}

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
}
