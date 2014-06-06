#include "WP8DataManager.h"

NS_CC_BEGIN

#define MAX_LEN  (16*1024 + 1)

std::string WP8Tran::tranChina(const char * pszFormat)
{
	char szBuf[MAX_LEN];
	strcpy(szBuf,pszFormat);

    WCHAR wszBuf[MAX_LEN] = {0};
    MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
    OutputDebugStringW(wszBuf);
    OutputDebugStringW(L"\n");

    WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(wszBuf), szBuf, sizeof(szBuf), NULL, FALSE);

	return szBuf;
}

Platform::String^ tranChinatops(std::string str)
{
	//return ref new Platform::String(cocos2d::WP8Tran::stows(cocos2d::WP8Tran::tranChina(str.c_str())).c_str());
	return WP8Tran::stops(WP8Tran::tranChina(str.c_str()));
}

std::wstring WP8Tran::stows(std::string str)
{
	setlocale(LC_ALL, "chs"); 
    const char* _Source = str.c_str();
    size_t _Dsize = str.size() + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest,_Source,_Dsize);
    std::wstring result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, "C");
    return result;
}
 
Platform::String^ WP8Tran::stops(std::string s)
{
    return ref new Platform::String(stows(s).c_str());
}
 
std::string WP8Tran::wstos(std::wstring ws)
{
    std::string s;
    s.assign(ws.begin(), ws.end());
    return s;
}
 
std::string WP8Tran::pstos(Platform::String^ ps)
{
    return wstos(std::wstring(ps->Data()));
}

NS_CC_END

static PhoneDirect3DXamlAppComponent::WP8DataManager^ m_wp8dataManager = ref new PhoneDirect3DXamlAppComponent::WP8DataManager();

WP8DataHelper::WP8DataHelper()
{

}

WP8DataHelper:: ~WP8DataHelper()
{

}

PhoneDirect3DXamlAppComponent::WP8DataManager^ WP8DataHelper::sharedWP8DataManager()
{
	return m_wp8dataManager;
}

void WP8DataHelper::purgeWP8Data()
{
	//delete m_wp8dataManager;
}