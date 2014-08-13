LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

#src_begin
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
../../Classes/ckbase/device/CKAndroidDeviceEngine.cpp \
../../Classes/ckbase/device/CKDeviceEngine.cpp \
../../Classes/ckbase/extentions/ckjson/CKJsonHelper.cpp \
../../Classes/ckbase/extentions/ckjson/CKJsonModel.cpp \
../../Classes/ckbase/extentions/messagebox/CKAndroidMessageBox.cpp \
../../Classes/ckbase/extentions/messagebox/CKMessageBox.cpp \
../../Classes/ckbase/extentions/notification/CKAndroidNotificationEngine.cpp \
../../Classes/ckbase/extentions/notification/CKNotificationEngine.cpp \
../../Classes/ckbase/extentions/pay/CKAndroidPayEngine.cpp \
../../Classes/ckbase/extentions/pay/CKPayEngine.cpp \
../../Classes/ckbase/extentions/rating/CKAndroidRatingEngine.cpp \
../../Classes/ckbase/extentions/rating/CKRatingDialog.cpp \
../../Classes/ckbase/extentions/rating/CKRatingEngine.cpp \
../../Classes/ckbase/extentions/trigger/acts.cpp \
../../Classes/ckbase/extentions/trigger/cons.cpp \
../../Classes/ckbase/network/CKHttpModel.cpp \
../../Classes/ckbase/network/CKHttpUtils.cpp \
../../Classes/ckbase/network/URLData.cpp \
../../Classes/ckbase/network/URLManager.cpp \
../../Classes/ckbase/wrapper/CKAndroidWrapper.cpp \
../../Classes/ckbase/wrapper/CKDate.cpp \
../../Classes/ckbase/wrapper/CKWrapper.cpp \
../../Classes/ckbase/wrapper/RSA_CryptionHandler.cpp \
../../Classes/FightScene.cpp \
../../Classes/game/colorgame/CKColorGameLayer.cpp \
../../Classes/game/colorgame/CKColorGameManager.cpp \
../../Classes/game/colorgame/CKColorGameScene.cpp \
../../Classes/game/colorgame/CKColorItem.cpp \
../../Classes/game/drawgame/CKSequenceLayer.cpp \
../../Classes/game/drawgame/DrawScene.cpp \
../../Classes/GUIScene.cpp \
../../Classes/HelloWorldScene.cpp 
#src_end

#c_begin
LOCAL_C_INCLUDES :=  \
$(LOCAL_PATH)/../../Classes \
$(LOCAL_PATH)/../../Classes/ckbase \
$(LOCAL_PATH)/../../Classes/ckbase/device \
$(LOCAL_PATH)/../../Classes/ckbase/extentions \
$(LOCAL_PATH)/../../Classes/ckbase/extentions/ckjson \
$(LOCAL_PATH)/../../Classes/ckbase/extentions/messagebox \
$(LOCAL_PATH)/../../Classes/ckbase/extentions/notification \
$(LOCAL_PATH)/../../Classes/ckbase/extentions/pay \
$(LOCAL_PATH)/../../Classes/ckbase/extentions/rating \
$(LOCAL_PATH)/../../Classes/ckbase/extentions/trigger \
$(LOCAL_PATH)/../../Classes/ckbase/network \
$(LOCAL_PATH)/../../Classes/ckbase/wrapper \
$(LOCAL_PATH)/../../Classes/game \
$(LOCAL_PATH)/../../Classes/game/colorgame \
$(LOCAL_PATH)/../../Classes/game/drawgame \
$(LOCAL_PATH)/../../thirdpartylibs \
$(LOCAL_PATH)/../../thirdpartylibs/openssl \
$(LOCAL_PATH)/../../thirdpartylibs/openssl/lib 
#c_end
					
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
