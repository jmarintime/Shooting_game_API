#include "stdafx.h"
#include "CollMgr.h"

#include "Obj.h"

CCollMgr::CCollMgr()
{
}


CCollMgr::~CCollMgr()
{
}

bool CCollMgr::Collrect(CObj * pTemp, CObj * pDest)
{
	RECT rc;

	if (IntersectRect(&rc, &pTemp->GetRect(), &pDest->GetRect()))
	{
		return true;
	}

	return false;
}

bool CCollMgr::Collcircle(CObj * pTemp, CObj * pDest)
{
	float	fsum = pTemp->GetInfo().fcx / 2 + pDest->GetInfo().fcx / 2;
	float	fWidth = pTemp->GetInfo().fx - pDest->GetInfo().fx;
	float	fheight = pTemp->GetInfo().fy - pDest->GetInfo().fy;

	float	fdistance = sqrt(fWidth*fWidth + fheight*fheight);

	if (fsum > fdistance)
		return true;

	return false;
}

bool CCollMgr::CollRcCir(CObj * pTemp, CObj * pDest)
{
	RECT	rc = pTemp->GetRect();

	if ((rc.top > pDest->GetInfo().fy || rc.bottom < pDest->GetInfo().fy) &&
		(rc.left > pDest->GetInfo().fx || rc.right < pDest->GetInfo().fx))
	{
		POINT temp[4];
		temp[0].x = rc.left;
		temp[0].y = rc.top;
		temp[1].x = rc.right;
		temp[1].y = rc.top;
		temp[2].x = rc.left;
		temp[2].y = rc.bottom;
		temp[3].x = rc.right;
		temp[3].y = rc.bottom;

		for (int i = 0; i < 4; ++i)
		{
			float	fsum = pDest->GetInfo().fcx / 2;
			float	fWidth = temp[i].x - pDest->GetInfo().fx;
			float	fheight = temp[i].y - pDest->GetInfo().fy;

			float	fdistance = sqrt(fWidth*fWidth + fheight*fheight);

			if (fsum - 4.f > fdistance)
				return true;
		}
	}
	else
	{
		POINT dest[4];
		for (int i = 0; i < 4; ++i)
		{
			dest[i] = pDest->GetPoint();
		}
		dest[0].x += (LONG)pDest->GetInfo().fcx / 2;
		dest[1].x -= (LONG)pDest->GetInfo().fcx / 2;
		dest[2].y += (LONG)pDest->GetInfo().fcy / 2;
		dest[3].y -= (LONG)pDest->GetInfo().fcy / 2;

		for (int i = 0; i < 4; ++i)
		{
			if (PtInRect(&rc, dest[i]))
				return true;
		}
	}

	return false;
}
