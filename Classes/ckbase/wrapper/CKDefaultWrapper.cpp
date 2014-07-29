#include "CKWrapper.h"

NS_WP_BGN

void showToast(const char* msg)
{
	if (strcmp(msg,"")==0)
	{
		msg = "empty";
	}
	
	auto label = LabelTTF::create(msg,"Arial", 24);

	auto scene = Director::getInstance()->getRunningScene();

	auto size = scene->getContentSize();

	int zOrder = getChildrenMaxZorder(scene);

	scene->addChild(label,zOrder);

	label->setPosition(ccp(size.width/2,label->getContentSize().height*2));

	label->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(1.0f),CCRemoveSelf::create(true)));
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
static wchar_t * Win32UTF82Unicode(const char* input) {
	wchar_t * result = NULL;
	int textlen;
	if (input) {
		textlen = MultiByteToWideChar(CP_ACP, 0, input, -1, NULL, 0);
		result = (wchar_t *) malloc((textlen + 1) * sizeof(wchar_t));
		memset(result, 0, (textlen + 1) * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, 0, input, -1, (LPWSTR) result, textlen);
	}
	return result;
}
#endif

void openUrl(const char* url)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	wchar_t * result = Win32UTF82Unicode(url);
	ShellExecute(NULL, L"open", result, NULL, NULL, SW_SHOWNORMAL);
	if (result) {
		free(result);
	}
#endif
}

NS_WP_END