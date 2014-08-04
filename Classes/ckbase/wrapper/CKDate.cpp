#include "CKDate.h"

using namespace cocos2d;

CKDate::CKDate() : currentTime(0)
{
	init();
}

CKDate* CKDate::date()
{
	CKDate* ret = new CKDate();
    ret->autorelease();
    return ret;
}

void CKDate::init()
{
	 time(&currentTime);
}

char* CKDate::toString()
{
	return asctime(localtime(&currentTime));
}

time_t CKDate::getTime()
{
	return currentTime;
}

void CKDate::setTime(time_t time)
{
	currentTime = time;
}

time_t CKDate::timeIntervalSinceDate(CKDate* otherDate)
{
    time_t beforTime = 0;
	if (otherDate)
		beforTime = otherDate->getTime();
    else
        beforTime = currentTime;

    return currentTime - beforTime;
}

// 标准时间格式字符串 YYYY-MM-DD HH:mm:ss
std::string CKDate::toStandardString()
{
	  char tmpbuf[20] = {0};
	  strftime(tmpbuf, 20, "%Y-%m-%d %H:%M:%S", localtime(&currentTime)); 
	  return tmpbuf;
}

// 标准时间格式字符串 YYYY-MM-DD HH:mm:ss
std::string CKDate::toShortString()
{
	  char tmpbuf[10] = {0};
      tm* _temp = localtime(&currentTime);
      //sprintf( tmpbuf,"%H:%M:%S",_temp->tm_hour,_temp->tm_min,_temp->tm_sec );
	  strftime(tmpbuf, 10, "%H:%M:%S", localtime(&currentTime)); 
	  return tmpbuf;
}

// 根据"YYYY-MM-DD HH:mm:ss"，转化为time_t
void CKDate::setTimeWithStandardString( char* pszStandardString )
{
	char *pStart = pszStandardString;
	char *pTmp = pStart;
	int count = 0;
	std::vector<std::string> vecStr;

	while(*pTmp++)
	{
		if (*pTmp == '-' || *pTmp == ':' || *pTmp == ' ' || *pTmp == '\0')
		{
			std::string tmpStr(pStart, count+1);
			vecStr.push_back(tmpStr);
			count = 0;
			pTmp++;
			pStart = pTmp;
		}
		else
		{
			count++;
		}
	}

	tm tTimeInfo;
	tTimeInfo.tm_year = atoi(vecStr[0].c_str()) - 1900;
	tTimeInfo.tm_mon = atoi(vecStr[1].c_str()) - 1;
	tTimeInfo.tm_mday = atoi(vecStr[2].c_str());
	tTimeInfo.tm_hour = atoi(vecStr[3].c_str());
	tTimeInfo.tm_min = atoi(vecStr[4].c_str());
	tTimeInfo.tm_sec = atoi(vecStr[5].c_str());

	currentTime = mktime(&tTimeInfo);

}

// 获取YYYYMMDD格式的日期，如20130423 
int CKDate::getCurrentDate()
{
	int nCurTime=0;
	struct tm *curTime;
	curTime=localtime(&currentTime);
	
	nCurTime = (curTime->tm_year+1900)*10000 +
			   (curTime->tm_mon+1)*100 + 
			   (curTime->tm_mday);

	return nCurTime;
}
