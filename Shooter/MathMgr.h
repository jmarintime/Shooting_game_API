#pragma once
#include "Obj.h"

class CMathMgr
{
public:
	static float GetDistance(const CObj* pTemp, const CObj* pDest)
	{
		float	fwidth = pTemp->GetInfo().fx - pDest->GetInfo().fx;
		float	fheight = pTemp->GetInfo().fy - pDest->GetInfo().fy;
		float	fdistance = sqrt(fwidth*fwidth + fheight*fheight);

		return fdistance;
	}
	static float GetAngle(const CObj* pTarget, const CObj* pSelf)
	{
		float	fwidth = pTarget->GetInfo().fx - pSelf->GetInfo().fx;
		float	fheight = pTarget->GetInfo().fy - pSelf->GetInfo().fy;
		float	fdistance = sqrt(fwidth*fwidth + fheight*fheight);

		float	fAngle = acosf(fwidth / fdistance) * 180 / PI;

		if (pTarget->GetInfo().fy > pSelf->GetInfo().fy)
			fAngle = 360 - fAngle;

		return fAngle;
	}
	static float GetAngle(const CObj* pTarget, const INFO pSelf)
	{
		float	fwidth = pTarget->GetInfo().fx - pSelf.fx;
		float	fheight = pTarget->GetInfo().fy - pSelf.fy;
		float	fdistance = sqrt(fwidth*fwidth + fheight*fheight);

		float	fAngle = acosf(fwidth / fdistance) * 180 / PI;

		if (pTarget->GetInfo().fy > pSelf.fy)
			fAngle = 360 - fAngle;

		return fAngle;
	}
public:
	CMathMgr();
	~CMathMgr();
};

