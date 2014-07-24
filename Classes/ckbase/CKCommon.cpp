#include "CKCommon.h"

const char* longToString(const long value) {

	static char buf[32];

	sprintf(buf, "%ld", value);

	return buf;
}

const char* intToString(const int value) {

	static char buf[24];

	sprintf(buf, "%d", value);

	return buf;
}
const char* floatToString(const float value) {
	static char buf[24];

	sprintf(buf, "%f", value);

	return buf;
}

const char* doubleToString(const double value) {
	static char buf[24];

	sprintf(buf, "%f", value);

	return buf;
}

std::string GBKToUTF8(const std::string& strGBK) {
	std::string strOutUTF8 = strGBK.c_str();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	WCHAR * str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char * str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete[] str1;
	str1 = NULL;
	delete[] str2;
	str2 = NULL;
#endif

	return strOutUTF8;
}
std::wstring UTF8ToUnicode(const char* putf8) {

	assert(putf8);

	std::wstring output;

	int len = strlen(putf8);

	if (len > 0) {
		wchar_t result;

		for (int i = 0; i < len;) {
			if (0 == (0x80 & putf8[i])) {//one byte
				result = (wchar_t) putf8[i++];
				output.push_back(result);
				continue;
			}

			if (0xe0 == (0xe0 & putf8[i])) {//three byte

				result = (putf8[i] & 0x1F) << 12;
				result |= (putf8[i + 1] & 0x3F) << 6;
				result |= (putf8[i + 2] & 0x3F);
				output.push_back(result);

				i += 3;

				continue;
			}

			if (0xc0 == (0xc0 & putf8[i])) {//two byte
				result = (putf8[i] & 0x1F) << 6;
				result |= (putf8[i + 1] & 0x3F);
				output.push_back(result);

				i += 2;

			}
		}

		//output.push_back(L'\0');
	}

	return output;
}

std::string UnicodeToUTF8(const wchar_t* putf8) {
	std::string output;

	wchar_t result;

	while (*putf8 != L'\0') {

		result = *putf8;

		if (result < 0x80) {

			output.push_back(char(0x7F & result));

			putf8++;

			continue;
		}
		if (result < 0x800) {

			output.push_back(char(0xc0 | ((result >> 6) & 0x1F)));
			output.push_back(char(0x80 | (result & 0x3F)));

			putf8++;

			continue;
		}

		if (result <= 0xFFFF) {

			output.push_back(char(0xE0 | ((result >> 12) & 0x0F)));
			output.push_back(char(0x80 | ((result >> 6) & 0x3F)));
			output.push_back(char(0x80 | (result & 0x3F)));

			putf8++;

			continue;
		}

	}

	return output;
}

bool parseJsonFileToDocument(const std::string &fileName, rapidjson::Document &doc)
{
	bool bRet = false;
	do {
		std::string jsonpath = FileUtils::getInstance()->fullPathForFilename(fileName);
		std::string contentStr = FileUtils::getInstance()->getStringFromFile(jsonpath);
		doc.Parse<0>(contentStr.c_str());
		CC_BREAK_IF(doc.HasParseError());
		bRet = true;
	} while (0);
	return bRet;
}

bool parseJsonStrToDocument(const std::string &jsonStr, rapidjson::Document &doc)
{
	bool bRet = false;
	do {
		doc.Parse<0>(jsonStr.c_str());
		CC_BREAK_IF(doc.HasParseError());
		bRet = true;
	} while (0);
	return bRet;
}

bool writeFileData(const char * localPath, const char * fileData)
{
	FILE * pFile = fopen (localPath,"wb");

	if (pFile!=NULL)
	{
		size_t result = fwrite(fileData, 1, strlen(fileData), pFile);
		fclose(pFile);                    
		if (result != 0) {
			return true;
		} else {
			return false;        
		}
	}
	return false;
}

int getChildrenMaxZorder(Node* parent)
{
	int maxZoreder = 0;
	if (parent)
	{
		const auto& children = parent->getChildren();
		for (const auto& child : children)
		{
			if (maxZoreder<child->getLocalZOrder())
			{
				maxZoreder = child->getLocalZOrder();
			}		
		}
	}
	return maxZoreder;
}


const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="; 

/* */ 
std::string base64_encode(const char* data, int data_len) 
{ 
	//return data;
	int prepare = 0; 
	int ret_len; 
	int temp = 0; 
	char *ret = NULL; 
	char *f = NULL; 
	int tmp = 0; 
	char changed[4]; 
	int i = 0; 
	ret_len = data_len / 3; 
	temp = data_len % 3; 
	if (temp > 0) 
	{ 
		ret_len += 1; 
	} 
	ret_len = ret_len*4 + 1; 
	ret = (char *)malloc(ret_len); 

	if ( ret == NULL) 
	{ 
		printf("No enough memory.\n"); 
		exit(0); 
	} 
	memset(ret, 0, ret_len); 
	f = ret; 
	while (tmp < data_len) 
	{ 
		temp = 0; 
		prepare = 0; 
		memset(changed, '\0', 4); 
		while (temp < 3) 
		{ 
			//printf("tmp = %d\n", tmp); 
			if (tmp >= data_len) 
			{ 
				break; 
			} 
			prepare = ((prepare << 8) | (data[tmp] & 0xFF)); 
			tmp++; 
			temp++; 
		} 
		prepare = (prepare<<((3-temp)*8)); 
		//printf("before for : temp = %d, prepare = %d\n", temp, prepare); 
		for (i = 0; i < 4 ;i++ ) 
		{ 
			if (temp < i) 
			{ 
				changed[i] = 0x40; 
			} 
			else 
			{ 
				changed[i] = (prepare>>((3-i)*6)) & 0x3F; 
			} 
			*f = base[changed[i]]; 
			//printf("%.2X", changed[i]); 
			f++; 
		} 
	} 
	*f = '\0'; 

	std::string result(ret);

	if (ret!=NULL)
	{
		free(ret);
		ret = NULL;
	}

	return result; 
} 

/* */ 
static char find_pos(char ch)   
{ 
	char *ptr = (char*)strrchr(base, ch);//the last position (the only) in base[] 
	return (ptr - base); 
} 
/* */ 
std::string base64_decode(const char *data, int data_len) 
{ 
	//return data;
	int ret_len = (data_len / 4) * 3; 
	int equal_count = 0; 
	static char *ret = NULL; 
	char *f = NULL; 
	int tmp = 0; 
	int temp = 0; 
	int prepare = 0; 
	int i = 0; 
	if (*(data + data_len - 1) == '=') 
	{ 
		equal_count += 1; 
	} 
	if (*(data + data_len - 2) == '=') 
	{ 
		equal_count += 1; 
	} 
	if (*(data + data_len - 3) == '=') 
	{//seems impossible 
		equal_count += 1; 
	} 
	switch (equal_count) 
	{ 
	case 0: 
		ret_len += 4;//3 + 1 [1 for NULL] 
		break; 
	case 1: 
		ret_len += 4;//Ceil((6*3)/8)+1 
		break; 
	case 2: 
		ret_len += 3;//Ceil((6*2)/8)+1 
		break; 
	case 3: 
		ret_len += 2;//Ceil((6*1)/8)+1 
		break; 
	} 
	ret = (char *)malloc(ret_len); 
	if (ret == NULL) 
	{ 
		printf("No enough memory.\n"); 
		exit(0); 
	} 
	memset(ret, 0, ret_len); 
	f = ret; 
	while (tmp < (data_len - equal_count)) 
	{ 
		temp = 0; 
		prepare = 0; 
		while (temp < 4) 
		{ 
			if (tmp >= (data_len - equal_count)) 
			{ 
				break; 
			} 
			prepare = (prepare << 6) | (find_pos(data[tmp])); 
			temp++; 
			tmp++; 
		} 
		prepare = prepare << ((4-temp) * 6); 
		for (i=0; i<3 ;i++ ) 
		{ 
			if (i == temp) 
			{ 
				break; 
			} 
			*f = (char)((prepare>>((2-i)*8)) & 0xFF); 
			f++; 
		} 
	} 
	*f = '\0'; 

	std::string result(ret);

	if (ret!=NULL)
	{
		free(ret);
		ret = NULL;
	}
	return result;
}