#pragma once
#include "Define.h"

class CDevice
{
private:
	//directx sdk (마이크로소프트에서 컴퓨터에있는 하드웨어를 쉽게 사용할수 있게
	// 여러가지 함수와, 데이터형을 제공해놓은 헤더파일과 라이브러리파일의 집합.)
	//다이렉트 사운드 인터페이스
	LPDIRECTSOUND				m_pSound;			//사운드카드를 대표하는 객체.
	vector<LPDIRECTSOUNDBUFFER>	m_vecSoundBuff;		//사운드파일을 로드해서 저장할 벡터

public:
	HRESULT Init();		//장치를 초기화
	HRESULT LoadWave(TCHAR* pFileName); //파일경로를 통해 파일을 읽어들이겠다.
	void SoundPlay(int iIndex, DWORD dwFlag); //몇번째 파일을 몇번 재생할지
	void SoundStop(int iIndex); //파일재생 정지
	bool SoundPlaying(int iIndex); //현재 인덱스사운드가 재생되고 있는지 아닌지

public:
	DECLARE_SINGETON(CDevice);

private:
	CDevice();
public:
	~CDevice();
};

