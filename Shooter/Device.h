#pragma once
#include "Define.h"

class CDevice
{
private:
	//directx sdk (����ũ�μ���Ʈ���� ��ǻ�Ϳ��ִ� �ϵ��� ���� ����Ҽ� �ְ�
	// �������� �Լ���, ���������� �����س��� ������ϰ� ���̺귯�������� ����.)
	//���̷�Ʈ ���� �������̽�
	LPDIRECTSOUND				m_pSound;			//����ī�带 ��ǥ�ϴ� ��ü.
	vector<LPDIRECTSOUNDBUFFER>	m_vecSoundBuff;		//���������� �ε��ؼ� ������ ����

public:
	HRESULT Init();		//��ġ�� �ʱ�ȭ
	HRESULT LoadWave(TCHAR* pFileName); //���ϰ�θ� ���� ������ �о���̰ڴ�.
	void SoundPlay(int iIndex, DWORD dwFlag); //���° ������ ��� �������
	void SoundStop(int iIndex); //������� ����
	bool SoundPlaying(int iIndex); //���� �ε������尡 ����ǰ� �ִ��� �ƴ���

public:
	DECLARE_SINGETON(CDevice);

private:
	CDevice();
public:
	~CDevice();
};

