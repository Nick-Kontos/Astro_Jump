#pragma once
#include <windows.h>
#include <xaudio2.h>
#include <strsafe.h>
#include <shellapi.h>
#include <mmsystem.h>
#include <conio.h>
#include "DXUT/Optional/SDKwavefile.h"


class XAudio2BasicSound
{
public:
	IXAudio2* pXAudio2;
	IXAudio2MasteringVoice* pMasteringVoice;
	IXAudio2SourceVoice* pSourceVoice;
	HRESULT hr;
	bool isRunning;
	bool ifDestroyed=false;

	XAudio2BasicSound();
	~XAudio2BasicSound();
	int start(LPCWSTR file);

	void cleanup();
	void stopVoice();
	HRESULT PlayPCM(IXAudio2* pXaudio2, LPCWSTR szFilename);
	HRESULT FindMediaFileCch(WCHAR* strDestPath, int cchDest, LPCWSTR strFilename);
};