#ifndef __URLDATA_H__
#define __URLDATA_H__

#include "cocos2d.h"
#include "CKJsonData.h"

USING_NS_CC;
#define MAX_URL_NUM 20

typedef enum __URLRequestType
{
	k_BATTLE_FRIENDLY_RANK_LIST = 0,
	k_BATTLE_WORLD_RANK_LIST

}URLRequestType;

class URLRequestDelegate
{
public:
	virtual void URLRequestErrorCallback(URLRequestType action, int errorCode, void* extraInfo ) =0;
	virtual void URLRequestSuccessCallback(URLRequestType action, CKJsonData &j_data, void* extraInfo) = 0;
	virtual void GetPicCallback(URLRequestType action, unsigned char* data, int dataLen, void* extraInfo) = 0;
};

struct requestURLData
{
	CKJsonData* j_data;
	URLRequestType action;
	URLRequestDelegate* delegate;
	char* picURL;
	void* extraInfo;

	requestURLData()
	{
		j_data = NULL;
		picURL = "";
		delegate = NULL;
		extraInfo = NULL;
	}
};

using namespace std;

class URLData:public cocos2d::Ref
{
public:
	CREATE_FUNC(URLData);

	//添加Url     
	bool add(requestURLData urlData);

protected:
	URLData(void);
	
	~URLData(void);

	virtual bool init();  
	
	//用于存储Url
	requestURLData m_urlData[MAX_URL_NUM];

	//添加Url的index
	int m_addIndex;
};

#endif // __URLDATA_H__