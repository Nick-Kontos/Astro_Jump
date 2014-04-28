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
	XAudio2BasicSound();
	~XAudio2BasicSound();
	int start();

	HRESULT PlayPCM(IXAudio2* pXaudio2, LPCWSTR szFilename);
	HRESULT FindMediaFileCch(WCHAR* strDestPath, int cchDest, LPCWSTR strFilename);
};