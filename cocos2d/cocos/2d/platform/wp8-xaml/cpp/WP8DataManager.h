#ifndef __WP8DataManager_H__
#define __WP8DataManager_H__

#include "cocos2d.h"

namespace PhoneDirect3DXamlAppComponent 
{
	public delegate Platform::String^ GetUniqueIDDelegate();

	public delegate void ToastWP8Delegate(Platform::String^ msg);

	public ref class WP8DataManager sealed
	{
	public:
		WP8DataManager(void)
		{

		}
		///DeviceInfo
		void SetGetUniqueIDDelegate(GetUniqueIDDelegate^ del)
		{
			m_getUniqueIDDelegate = del;
		}

		Platform::String^ GetUniqueID()
		{			
			if(m_getUniqueIDDelegate)
			{
				return m_getUniqueIDDelegate->Invoke();
			}
			return "";
		}

		void SetToastWP8Delegate(ToastWP8Delegate^ del)
		{
			m_toastWP8Delegate = del;
		}

		void ToastWP8(Platform::String^ msg)
		{
			if(m_toastWP8Delegate)
			{
				m_toastWP8Delegate->Invoke(msg);
			}
		}
		///DeviceInfo end


	private:
		property static GetUniqueIDDelegate^ m_getUniqueIDDelegate;
		property static ToastWP8Delegate^ m_toastWP8Delegate;
	};
}

NS_CC_BEGIN

class CC_DLL WP8Tran
{
public:
	static std::string tranChina(const char * str);

	static Platform::String^ tranChinatops(std::string str);

	static std::wstring stows(std::string s);
 
	static Platform::String^ stops(std::string s);
 
	static std::string wstos(std::wstring ws);
 
	static std::string pstos(Platform::String^ ps);
};

NS_CC_END

class WP8DataHelper
{	
public:
    WP8DataHelper();
    virtual ~WP8DataHelper();

	static PhoneDirect3DXamlAppComponent::WP8DataManager^ sharedWP8DataManager();
	static void purgeWP8Data();
};
#endif // __WP8DataManager_H__
