#include "WP8DataEvent.h"
#include "Cocos2dRenderer.h"

namespace PhoneDirect3DXamlAppComponent
{
	
WP8RedeemEvent::WP8RedeemEvent(WP8RedeemEventType type,Platform::String^ code)
	:m_type(type),m_code(code)
{

}
WP8RedeemEvent::WP8RedeemEvent(WP8RedeemEventType type)
	:m_type(type)
{

}

void WP8RedeemEvent::execute(Cocos2dRenderer ^ renderer)
{
    switch(m_type)
    {
	case WP8RedeemEventType::WP8RedeemSuccess:
		//renderer->nativeRedeemSuccess(m_code.Get());
        break;
	case WP8RedeemEventType::WP8RedeemFailed:
		//renderer->nativeRedeemFailed();
        break;
    default:
       
        break;      
    }
}

}

