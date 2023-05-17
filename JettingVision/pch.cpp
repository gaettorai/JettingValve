// pch.cpp: 미리 컴파일된 헤더에 해당하는 소스 파일

#include "pch.h"

StateData g_StateData;

// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// DuasEots.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.


CString getCurrentPath()
{
	HMODULE hModule;
	hModule = ::GetModuleHandle(NULL); // handle of current module
	ASSERT(hModule != NULL);

	CString strExeFileName;
	VERIFY(::GetModuleFileName(hModule, strExeFileName.GetBuffer(_MAX_PATH), _MAX_PATH));
	strExeFileName.ReleaseBuffer();

	TCHAR Drive[_MAX_DRIVE];
	TCHAR Path[_MAX_PATH];
	TCHAR Filename[_MAX_FNAME];
	TCHAR Ext[_MAX_EXT];

#ifdef UNICODE
	_wsplitpath_s(strExeFileName.GetString(), Drive, Path, Filename, Ext);
#else
	_splitpath_s(strExeFileName.GetString(), Drive, Path, Filename, Ext);
#endif
	CString str, str1, str2;
	str1 = Drive;
	str2 = Path;
	str = str1 + str2;
	return str;//CString(Drive) + CString(Path); // has trailing backslash
}

/*
CString  str;           //형변환할 문자열이 저장된 CString 변수
wchar_t* wchar_str;     //첫번째 단계(CString to wchar_t*)를 위한 변수
char*    char_str;      //char* 형의 변수
int      char_str_len;  //char* 형 변수의 길이를 위한 변수

//1. CString to wchar_t* conversion

wchar_str = str.GetBuffer(str.GetLength());

//2. wchar_t* to char* conversion

//char* 형에 대한길이를 구함
char_str_len = WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, NULL, 0, NULL, NULL);
char_str = new char[char_str_len];  //메모리 할당
//wchar_t* to char* conversion
WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, char_str, char_str_len, 0,0);

*/
//유니코드 환경에서 CString 에서 char*로 변환
void TranseCStringToCharPointer(CString str, char retCh[])
{
	wchar_t* pWcharStr;  //첫번째 단계(CString to wchar_t*)를 위한 변수
	char* pChStr;		//char* 형의 변수
	int			nChStrLen;	//char* 형 변수의 길이를 위한 변수



	//1. CString to wchar_t* conversion
	pWcharStr = str.GetBuffer(str.GetLength());
	//2. wchar_t* to char* conversion
	nChStrLen = WideCharToMultiByte(CP_ACP, 0, pWcharStr, -1, NULL, 0, NULL, NULL);
	pChStr = new char[nChStrLen];
	//wchar_t* to char* conversion
	WideCharToMultiByte(CP_ACP, 0, pWcharStr, -1, pChStr, nChStrLen, 0, 0);

	str.ReleaseBuffer();

	strcpy_s(retCh, nChStrLen, pChStr);

	delete pChStr;

}
//유니코드 환경에서 char* 에서 CString으로 변환
CString TranseCharPointerToCString(char* ch)
{
	int			nLen;
	wchar_t* pWcharStr;//첫번째 단계 (char* to wchar_t*)를 위한 변수
	CString		strRet;

	//1. 멀티바이트 크기 계산 길이 반환
	nLen = MultiByteToWideChar(CP_ACP, 0, ch, -1, NULL, NULL);

	//wchar_t 메모리 할당
	pWcharStr = new WCHAR[nLen];

	//형변환
	MultiByteToWideChar(CP_ACP, 0, ch, strlen(ch) + 1, pWcharStr, nLen);

	strRet.Format(_T("%s"), pWcharStr);

	return strRet;
}

DWORD CreateNewFileAsUTF16(IN LPCTSTR lpszFilePath)
{
	HANDLE  hFile = INVALID_HANDLE_VALUE;
	DWORD   wBOM = 0xFEFF;
	DWORD   dwCbWritten = 0;

	hFile = ::CreateFile(lpszFilePath, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		return ::GetLastError();
	}
	::WriteFile(hFile, &wBOM, sizeof(WORD), &dwCbWritten, NULL);
	::CloseHandle(hFile);
	hFile = INVALID_HANDLE_VALUE;

	return ERROR_SUCCESS;
}


// 미리 컴파일된 헤더를 사용하는 경우 컴파일이 성공하려면 이 소스 파일이 필요합니다.