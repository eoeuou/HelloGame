package org.cocos2dx.cpp;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.provider.Settings;
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

	public static String getCKGamePackageName() {

		Log.d("CKGame", "pack " + sActivity.getPackageName());

		return sActivity.getPackageName();
	}

	public static String getPackageVersion() {
		String versionName = "0.0.0";
		try {
			versionName = sActivity.getPackageManager().getPackageInfo(
					sActivity.getPackageName(), 0).versionName;
			Log.d("CKGame", "version " + versionName);
		} catch (NameNotFoundException e) {
			Log.e("CKGame", "getPackageVersion error", e);
		}
		return versionName;
	}

	public static String getLocaleLanguage() {
		java.util.Locale locale = java.util.Locale.getDefault();
		String languageName = locale.getLanguage() + "_" + locale.getCountry();
		return languageName;
	}

	public static String getPhoneNum() {

		TelephonyManager tm = (TelephonyManager) sActivity
				.getSystemService(Context.TELEPHONY_SERVICE);

		String phoneNum = tm.getLine1Number();

		Log.d("CKGame", "phoneNum " + phoneNum);

		if (phoneNum != null) {
			return phoneNum;
		}

		return "";
	}

	public static String getDeviceModel() {
		return android.os.Build.MODEL;
	}

	public static int getNetworkStatus() {

		ConnectivityManager manager = (ConnectivityManager) sActivity
				.getSystemService(Context.CONNECTIVITY_SERVICE);

		NetworkInfo networkInfo = manager.getActiveNetworkInfo();

		if (networkInfo == null || !networkInfo.isAvailable()) {
			return 0;
		}

		int type = networkInfo.getType();

		if (ConnectivityManager.TYPE_WIFI == type) {
			return 1;
		}

		if (ConnectivityManager.TYPE_MOBILE == type) {
			return 2;
		}

		return 5;
	}

	public static void showNetworkSettings() {
		Intent intent = new Intent(Settings.ACTION_WIFI_SETTINGS);
		intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		sActivity.startActivity(intent);
	}

	// ===========================================================
	// CKAndroidDeviceEngine
	// ===========================================================

}
