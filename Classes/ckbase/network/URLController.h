#ifndef __URLCONTROLLER_H__
#define __URLCONTROLLER_H__

#include "cocos2d.h"
#include "CKCommon.h"
#include "CKHttpUtils.h"
#include "URLData.h"

USING_NS_CC;

using namespace std;

class URLController
{
public:

	CK_SINGLETON_METHOD_LAZY(URLController,s_singleInstance,Instance);

    static void destroyInstance();
	
	bool init();

	//************************************
	// Method:    openUrl
	// FullName:  URLController::openUrl
	// Access:    public 
	// Returns:   void
	// Qualifier: 请求url,回掉URLRequestListener中URLRequestCallback方法
	// Parameter: std::string url
	//************************************
	void openUrl(std::string url,URLRequestListener* urlRequestListener = nullptr);
			
private:
	URLController(void);
	
	~URLController(void);

	CC_SYNTHESIZE(std::string,m_strUrl,StrUrl);

	CC_SYNTHESIZE(URLRequestListener*,m_urlRequestListener,URLRequestListener);

};

#endif // __URLCONTROLLER_H__