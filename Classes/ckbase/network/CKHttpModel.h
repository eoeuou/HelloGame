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
	CK_SYNTHESIZE_MODEL_BOOLEAN(bool,"isSucceed",IsSucceed);

	/*[statusCode������״̬��]*/
	CK_SYNTHESIZE_MODEL_INTEGER(int,"statusCode",StatusCode);

	/*[path�������ַ]*/
	CK_SYNTHESIZE_MODEL_STRING(std::string,"path",Path);

	/*[content������]*/
	CK_SYNTHESIZE_MODEL_STRING(std::string,"content",Content);
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
