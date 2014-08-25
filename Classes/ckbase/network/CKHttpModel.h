#ifndef __CKHTTPMODEL_H__
#define __CKHTTPMODEL_H__

#include "cocos2d.h"
#include "CKModel.h"
#include "CKJsonModel.h"

USING_NS_CC;

using namespace std;

#define STD_FUN_CKHTTPMODEL_NULL [](CKHttpModel* model){}

/*
以下结果均来自CKHttpUtils 返回值
[content：内容] [path：保存地址] [statusCode：返回状态码] [isSucceed: 返回成功失败]
*/
class CKHttpModel : public CKModel
{
public:
	CREATE_FUNC(CKHttpModel);

	/*[isSucceed: 返回成功失败]*/
	CK_SYNTHESIZE_MODEL_BOOLEAN(bool,"isSucceed",IsSucceed);

	/*[statusCode：返回状态码]*/
	CK_SYNTHESIZE_MODEL_INTEGER(int,"statusCode",StatusCode);

	/*[path：保存地址]*/
	CK_SYNTHESIZE_MODEL_STRING(std::string,"path",Path);

	/*[content：内容]*/
	CK_SYNTHESIZE_MODEL_STRING(std::string,"content",Content);
	/*json数据*/
	CC_SYNTHESIZE_READONLY(CKJsonModel*,m_curCKJsonModel,CurCKJsonModel);

	//************************************
	// Method:    initModelData
	// FullName:  CKHttpModel::initModelData
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: bool isSucceed 返回成功失败
	// Parameter: int statusCode 返回状态码
	// Parameter: std::string path 保存地址
	// Parameter: std::string content 内容
	// Parameter: CKJsonModel * jsonModel 
	//************************************
	void initModelData(bool isSucceed, int statusCode,std::string path, std::string content,CKJsonModel* jsonModel);
protected:

	CKHttpModel();

	~CKHttpModel();

};

#endif // __CKHTTPMODEL_H__
