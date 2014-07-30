package org.cocos2dx.ckbase.thirdsdk.cocospush;

import org.cocos2dx.ckbase.Wrapper;

import com.cocos.CCPush;

public class CocosPush {

	public static void initCocosPush() {
		// 设置debug模式
		CCPush.setDebugMode(true);
		// 初始化push
		CCPush.init(Wrapper.getActivity().getApplicationContext());
		CCPush.startPush(Wrapper.getActivity().getApplicationContext());
	}
}
