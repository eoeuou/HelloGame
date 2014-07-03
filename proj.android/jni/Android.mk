LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
					../../Classes/AppDelegate.cpp \
					../../Classes/ckbase/CKCommon.cpp \
					../../Classes/ckbase/CKConstants.cpp \
					../../Classes/ckbase/CKDialog.cpp \
					../../Classes/ckbase/CKGameDataManager.cpp \
					../../Classes/ckbase/CKGameManager.cpp \
					../../Classes/ckbase/CKModel.cpp \
					../../Classes/ckbase/CKProtocols.cpp \
					../../Classes/ckbase/CKScene.cpp \
					../../Classes/ckbase/wrapper/CKAndroidWrapper.cpp \
					../../Classes/ckbase/device/CKAndroidDeviceEngine.cpp \
					../../Classes/ckbase/device/CKDeviceEngine.cpp \
					../../Classes/ckbase/extentions/ckjson/CKJsonData.cpp \
					../../Classes/ckbase/extentions/ckjson/CKJsonHelper.cpp \
					../../Classes/ckbase/extentions/notification/CKAndroidNotificationEngine.cpp \
					../../Classes/ckbase/extentions/notification/CKNotificationEngine.cpp \
					../../Classes/ckbase/extentions/pay/CKAndroidPayEngine.cpp \
					../../Classes/ckbase/extentions/pay/CKPayEngine.cpp \
					../../Classes/ckbase/extentions/trigger/acts.cpp \
					../../Classes/ckbase/extentions/trigger/cons.cpp \
					../../Classes/ckbase/network/CKHttpUtils.cpp \
					../../Classes/FightScene.cpp \
					../../Classes/HelloWorldScene.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/ckbase \
					$(LOCAL_PATH)/../../Classes/ckbase/device \
					$(LOCAL_PATH)/../../Classes/ckbase/extentions \
					$(LOCAL_PATH)/../../Classes/ckbase/extentions/ckjson \
					$(LOCAL_PATH)/../../Classes/ckbase/extentions/notification \
					$(LOCAL_PATH)/../../Classes/ckbase/extentions/pay \
					$(LOCAL_PATH)/../../Classes/ckbase/extentions/trigger \
					$(LOCAL_PATH)/../../Classes/ckbase/network \
					$(LOCAL_PATH)/../../cocos2d/extensions \
					$(LOCAL_PATH)/../../cocos2d/cocos/network \
					
					
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_ui_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)
$(call import-module,extensions)
$(call import-module,editor-support/cocostudio)
$(call import-module,ui)
$(call import-module,network)
