using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PhoneDirect3DXamlAppComponent.GameSdkBridge;
using GameSDK;
using GameSDK.Callback;
using Microsoft.Phone.Controls;
namespace PhoneDirect3DXamlAppInterop
{
    public class GameSdkBridge : ICallback
    {
        public void InitializeSDK()
        {
            GameBilling.InitializeSDK();
        }
        public void GetVerificationCode(string billingIndex, string phoneNumber, object callback)
        {
           
            GameBilling.GetVerificationCode(billingIndex, phoneNumber, (IPayCallback)callback);
          
        }
        public void PayWithUI(object page, string billingIndex,string cpParam, object callback)
        {
            GameBilling.PayWithUI((PhoneApplicationPage)page, billingIndex,cpParam, (IPayCallback)callback);
        }
    }
}
