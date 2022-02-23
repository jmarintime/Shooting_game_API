#pragma once

class CBridge;
class CObj;
template <typename T>
class CObjFactory
{
public:
	static CObj* CreateObj()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		
		return pObj;
	}
	static CObj* CreateObj(float _fx, float _fy)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(_fx, _fy);

		return pObj;
	}
	static CObj* CreateObj(float _fx, float _fy, CBridge* _pbridge)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(_fx, _fy);

		_pbridge->SetObj(pObj);
		_pbridge->Initialize();

		((T*)pObj)->SetBridge(_pbridge);

		return pObj;
	}
public:
	CObjFactory();
	~CObjFactory();
};

