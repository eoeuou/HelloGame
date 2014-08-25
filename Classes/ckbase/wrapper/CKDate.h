
#ifndef __CLASSES_DATE_H__
#define __CLASSES_DATE_H__

#include <string>
#include "cocos2d.h"

class CKDate : public cocos2d::CCObject
{
public:
	CKDate();
	~CKDate() {};

	// 用字符串表示的时间，格式类似为 "Sat May 20 17:36:17 2000"
	char* toString();

	// 标准时间格式字符串，格式类似为 "YYYY-MM-DD HH:mm:ss"
	std::string toStandardString();
    // 短时间格式字符串 格式为"HH:mm:ss"    
    std::string toShortString();
	// 根据"YYYY-MM-DD HH:mm:ss"，转化为time_t
	void setTimeWithStandardString(char* pszStandardString);

	time_t getTime();
	void setTime(time_t time);
    time_t timeIntervalSinceDate(CKDate* otherDate);

	// 获取YYYYMMDD格式的日期，如20130423 
	int getCurrentDate();

	static CKDate* date();

private:
	void init();
	// 1970年1月1号到现在的秒数 
	time_t currentTime;
};

#endif // __CLASSES_DATE_H__
