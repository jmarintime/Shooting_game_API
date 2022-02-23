#pragma once
#include "Include.h"

class CKeyMgr
{
private:
	DWORD	m_dwKey;

public:
	DWORD GetKey() const { return m_dwKey; }
	void CheckKey();

public:
	DECLARE_SINGETON(CKeyMgr);

private:
	CKeyMgr();
public:
	~CKeyMgr();
};

