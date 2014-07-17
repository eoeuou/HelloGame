#ifndef __URLDATA_H__
#define __URLDATA_H__

#include "cocos2d.h"
#include "CKJsonModel.h"
#include "CKHttpModel.h"

USING_NS_CC;
using namespace std;

#define MAX_URL_NUM 3

typedef enum __URLRequestType
{
	k_URL_NULL = 0,
	k_BATTLE_FRIENDLY_RANK_LIST,
	k_BATTLE_WORLD_RANK_LIST

}URLRequestType;

/*URLController 中openUrl 方法的回掉*/
class URLRequestListener
{
public:
	virtual void urlRequestCallback(CKHttpModel* model) = 0;
};

struct requestURLData
{
	CKJsonModel* m_jsonModel;
	URLRequestType m_action;
	URLRequestListener* m_listener;
	char* m_picURL;
	void* m_extraInfo;

	requestURLData()
	{
		m_jsonModel = nullptr;
		m_action =  URLRequestType::k_URL_NULL;
		m_listener = nullptr;
		m_picURL = "";
		m_extraInfo = nullptr;
	}

	void clear()
	{
		m_jsonModel = nullptr;
		m_action =  URLRequestType::k_URL_NULL;
		m_listener = nullptr;
		m_picURL = "";
		m_extraInfo = nullptr;	
	}
};

class URLData:public cocos2d::Ref
{
public:
	CREATE_FUNC(URLData);

	//添加Url     
	bool add(requestURLData urlData);

	string getNextUrl();

	std::string getCurUrl();

	requestURLData* getCurUrlData();

	//************************************
	// Method:    removeCurRUrlData
	// FullName:  URLData::removeCurRUrlData
	// Access:    public 
	// Returns:   void
	// Qualifier: 删除当前请求数据
	//************************************
	void removeCurRUrlData();

	void clear();

	bool isEmpty();

protected:
	URLData(void);
	
	~URLData(void);

	virtual bool init();  
	
	//用于存储Url
	requestURLData m_rUrlData[MAX_URL_NUM];

	//添加Url的index
	int m_addIndex;
	
	//
	int m_getIndex;

private:
	std::string generateURL(URLRequestType type);
};

#endif // __URLDATA_H__