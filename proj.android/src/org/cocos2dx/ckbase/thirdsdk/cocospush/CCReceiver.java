package org.cocos2dx.ckbase.thirdsdk.cocospush;

import java.util.List;

import android.content.Context;
import android.util.Log;

import com.cocos.CCPushRecevier;

public class CCReceiver extends CCPushRecevier {
	@Override
	public void onSetTags(Context context, int retCode,
			List<String> sucessTags, List<String> failTags) {
		String contentText = "onSetTags retCode=" + retCode + "\n sucessTags="
				+ sucessTags + "\n failTags=" + failTags;

		Log.d("ClientTestRecevier", "========" + contentText);
	}

	@Override
	public void onDelTags(Context context, int retCode,
			List<String> sucessTags, List<String> failTags) {
		String contentText = "onDelTags retCode=" + retCode + " sucessTags="
				+ sucessTags + " failTags=" + failTags;

		Log.d("ClientTestRecevier", "========" + contentText);
	}

	@Override
	public void onStartPush(Context context, int retCode) {
		String contentText = "onStartPush retCode=" + retCode;

		Log.d("ClientTestRecevier", "========" + contentText);
	}

	@Override
	public void onStopPush(Context context, int retCode) {
		String contentText = "onStopPush retCode=" + retCode;

		Log.d("ClientTestRecevier", "========" + contentText);
	}

	@Override
	public void onSetAccount(Context context, int retCode, String account) {
		String contentText = "onSetAccount retCode=" + retCode + " account="
				+ account;

		Log.d("ClientTestRecevier", "========" + contentText);
	}

	@Override
	public void onDelAccount(Context context, int retCode) {
		String contentText = "onDelAccount retCode=" + retCode;

		Log.d("ClientTestRecevier", "========" + contentText);
	}

	@Override
	public void onLocalTimer(Context arg0, String arg1) {
		Log.d("ClientTestRecevier", "========onLocalTimer arg1=" + arg1);
	}

	@Override
	public void onMessage(Context arg0, String arg1) {
		Log.d("ClientTestRecevier", "========onMessage arg1=" + arg1);
	}
}
