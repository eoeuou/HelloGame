#!/bin/bash
python build_native.py

ant clean

ant debug
#ant release

ant installr

adb shell am start -a android.intent.action.MAIN -c android.intent.category.LAUNCHER -n com.chukong.HelloGame/org.cocos2dx.cpp.AppActivity

#adb logcat -s *:I
#adb logcat | grep 'D/cocos2d-x'

