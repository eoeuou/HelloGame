#ifndef __URLDATA_H__
#define __URLDATA_H__

#include "cocos2d.h"
#include "CKJsonModel.h"

USING_NS_CC;
#define MAX_URL_NUM 20

typedef enum __URLRequestType
{
	k_BATTLE_FRIENDLY_RANK_LIST = 0,
	k_BATTLE_WORLD_RANK_LIST

}URLRequestType;

/*URLController 中openUrl 方法的回掉*/
class URLRequestListener
{
public:
	virtual void URLRequestCallback(CKHttpModel* model) = 0;
};

struct requestURLData
{
	CKJsonModel* j_data;
	URLRequestType action;
	URLRequestListener* delegate;
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

	string getNextUrl();

	std::string getCurUrl();

	requestURLData* getCurUrlData();

	void clear();

	bool isEmpty();

protected:
	URLData(void);
	
	~URLData(void);

	virtual bool init();  
	
	//用于存储Url
	requestURLData m_urlData[MAX_URL_NUM];

	//添加Url的index
	int m_addIndex;
	
	//
	int m_getIndex;

private:
	std::string generateURL(URLRequestType type);
};

#endif // __URLDATA_H__