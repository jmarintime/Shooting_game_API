#pragma once

typedef struct tagInfo
{
	float	fx;
	float	fy;
	float	fcx;
	float	fcy;
	int		iLayer;

	tagInfo() {};
	tagInfo(float _fx, float _fy)
	: fx(_fx), fy(_fy), iLayer(0) {};
	tagInfo(float _fx, float _fy, float _fcx, float _fcy)
		: fx(_fx), fy(_fy), fcx(_fcx), fcy(_fcy), iLayer(0) {};
	tagInfo(float _fx, float _fy, float _fcx, float _fcy, int _layer)
		: fx(_fx), fy(_fy), fcx(_fcx), fcy(_fcy), iLayer(_layer) {};

}INFO;

typedef struct tagFrame
{
	int		iStart;
	int		iLast;
	int		iScene;
	DWORD	dwTime;

	tagFrame() {};
	tagFrame(int _start, int _last, int _scene, DWORD _time)
	: iStart(_start), iLast(_last), iScene(_scene), dwTime(_time) {};

}FRAME;

typedef struct tagScroll
{
	int ileft;
	int itop;
	int iright;
	int ibottom;

	tagScroll() {};
	tagScroll(int _top, int _bottom, int _left, int _right)
	: ileft(_left), itop(_top), iright(_right), ibottom(_bottom) {};

}SCROLL;

typedef struct setStat
{
	int		iHP;
	int		iMaxHP;

	int		iAtt;

	setStat() {};
	setStat(int _hp)
	: iHP(_hp), iMaxHP(_hp) {};

}STAT;