#ifndef __WP8DATA_EVENT__
#define __WP8DATA_EVENT__

#include <agile.h>
#include "InputEvent.h"

ref class Cocos2dRenderer;

namespace PhoneDirect3DXamlAppComponent
{
	
public enum class WP8RedeemEventType{
	WP8RedeemFailed,
	WP8RedeemSuccess
};

class WP8RedeemEvent: public InputEvent
{	
public:
	WP8RedeemEvent(WP8RedeemEventType type,Platform::String^ code);
	WP8RedeemEvent(WP8RedeemEventType type);

    virtual void execute(Cocos2dRenderer ^ renderer);

private:
	Platform::Agile<Platform::String> m_code;
	WP8RedeemEventType m_type;
};


}

#endif // #ifndef __WP8DATA_EVENT__

