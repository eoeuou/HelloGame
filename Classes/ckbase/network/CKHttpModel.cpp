#include "CKHttpModel.h"

CKHttpModel::CKHttpModel(void):
	m_curCKJsonModel(nullptr)
{
}


CKHttpModel::~CKHttpModel(void)
{
	
}

void CKHttpModel::initModelData(bool isSucceed, int statusCode,std::string path, std::string content,CKJsonModel* jsonModel)
{
	isSucceed = this->getIsSucceed();	
	statusCode = this->getStatusCode();
	path = this->getPath();
	content = this->getContent();
	jsonModel = this->getCurCKJsonModel();

	if (isSucceed)
	{
		this->setValue("isSucceed",Value(isSucceed));
	}
	if (statusCode != 0)
	{
		this->setValue("statusCode",Value(statusCode));
	}
	if (path != "")
	{
		this->setValue("path",Value(path));
	}
	if (content != "")
	{
		this->setValue("content",Value(content));
	}
	this->m_curCKJsonModel = jsonModel;
}