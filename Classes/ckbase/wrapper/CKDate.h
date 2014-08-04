
#ifndef __CLASSES_DATE_H__
#define __CLASSES_DATE_H__

#include <string>
#include "cocos2d.h"

class CKDate : public cocos2d::CCObject
{
public:
	CKDate();
	~CKDate() {};

	// ���ַ�����ʾ��ʱ�䣬��ʽ����Ϊ "Sat May 20 17:36:17 2000"
	char* toString();

	// ��׼ʱ���ʽ�ַ�������ʽ����Ϊ "YYYY-MM-DD HH:mm:ss"
	std::string toStandardString();
    // ��ʱ���ʽ�ַ��� ��ʽΪ"HH:mm:ss"    
    std::string toShortString();
	// ����"YYYY-MM-DD HH:mm:ss"��ת��Ϊtime_t
	void setTimeWithStandardString(char* pszStandardString);

	time_t getTime();
	void setTime(time_t time);
    time_t timeIntervalSinceDate(CKDate* otherDate);

	// ��ȡYYYYMMDD��ʽ�����ڣ���20130423 
	int getCurrentDate();

	static CKDate* date();

private:
	void init();
	// 1970��1��1�ŵ����ڵ����� 
	time_t currentTime;
};

#endif // __CLASSES_DATE_H__
