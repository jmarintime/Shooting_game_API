#include "stdafx.h"
#include "SceneObj.h"


CSceneObj::CSceneObj()
{
}


CSceneObj::~CSceneObj()
{
}

void CSceneObj::Release()
{
	for (map<string, CBitMap*>::iterator iter = m_MapBmp.begin(); iter != m_MapBmp.end(); ++iter)
	{
		Safe_Delete(iter->second);
	}
	m_MapBmp.clear();
}