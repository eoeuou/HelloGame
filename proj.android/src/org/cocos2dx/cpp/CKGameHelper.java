package org.cocos2dx.cpp;

import android.app.Activity;
import android.content.Context;
import android.telephony.TelephonyManager;
import android.util.Log;

public class CKGameHelper {

	private static Activity sActivity = null;

	private static boolean sInited = false;

	public static void init(final Activity activity) {
		if (!sInited) {

			sActivity = activity;

			sInited = true;
		}
	}

	public static Activity getActivity() {
		return sActivity;
	}

	// ===========================================================
	// CKAndroidDeviceEngine
	// ===========================================================
	public static String getDeviceId() {

		TelephonyManager tm = (TelephonyManager) sActivity
				.getSystemService(Context.TELEPHONY_SERVICE);

		String deviceId = tm.getDeviceId();

		if (deviceId == null) {
			deviceId = "000000";
		}

		Log.d("CKGame", "deviceid " + deviceId);

		return deviceId;
	}

	public static int getDeviceCallState() {

		TelephonyManager tm = (TelephonyManager) sActivity
				.getSystemService(Context.TELEPHONY_SERVICE);

		int callstate = tm.getCallState();

		Log.d("CKGame", "callstate " + callstate);

		return callstate;
	}

	// ===========================================================
	// CKAndroidDeviceEngine
	// ===========================================================

}
