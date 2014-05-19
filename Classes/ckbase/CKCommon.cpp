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

bool parseJsonToDocument(const std::string &fileName, rapidjson::Document &doc)
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
