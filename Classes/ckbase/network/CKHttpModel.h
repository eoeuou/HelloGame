#ifndef __CKHTTPMODEL_H__
#define __CKHTTPMODEL_H__

#include "cocos2d.h"
#include "CKModel.h"
#include "CKJsonModel.h"

USING_NS_CC;

using namespace std;

#define STD_FUN_CKHTTPMODEL_NULL [](CKHttpModel* model){}

/*
���½��������CKHttpUtils ����ֵ
[content������] [path�������ַ] [statusCode������״̬��] [isSucceed: ���سɹ�ʧ��]
*/
class CKHttpModel : public CKModel
{
public:
	CREATE_FUNC(CKHttpModel);

	/*[isSucceed: ���سɹ�ʧ��]*/
	bool getIsSucceed(){ return this->getValue("isSucceed",Value(false)).asBool(); };

	/*[statusCode������״̬��]*/
	int getStatusCode(){ return this->getValue("statusCode").asInt(); };

	/*[path�������ַ]*/
	std::string getPath(){ return this->getValue("path").asString(); };

	/*[result������]*/
	std::string getContent(){ return this->getValue("content").asString(); };
		
	/*json����*/
	CC_SYNTHESIZE_READONLY(CKJsonModel*,m_curCKJsonModel,CurCKJsonModel);

	//************************************
	// Method:    initModelData
	// FullName:  CKHttpModel::initModelData
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: bool isSucceed ���سɹ�ʧ��
	// Parameter: int statusCode ����״̬��
	// Parameter: std::string path �����ַ
	// Parameter: std::string content ����
	// Parameter: CKJsonModel * jsonModel 
	//************************************
	void initModelData(bool isSucceed, int statusCode,std::string path, std::string content,CKJsonModel* jsonModel);
protected:

	CKHttpModel();

	~CKHttpModel();

};

#endif // __CKHTTPMODEL_H__
