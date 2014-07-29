package org.cocos2dx.ckbase;

import java.io.File;
import java.util.List;

import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Debug;
import android.os.Environment;
import android.os.StatFs;
import android.provider.Settings;
import android.telephony.TelephonyManager;
import android.text.format.Formatter;
import android.util.Log;

public class CKGameHelper {
	// ===========================================================
	// CKAndroidDeviceEngine
	// ===========================================================
	public static String getDeviceId() {

		TelephonyManager tm = (TelephonyManager) Wrapper.getActivity()
				.getSystemService(Wrapper.getActivity().TELEPHONY_SERVICE);

		String deviceId = tm.getDeviceId();

		if (deviceId == null) {
			deviceId = "000000";
		}

		Log.d("CKGame", "deviceid " + deviceId);

		return deviceId;
	}

	public static int getDeviceCallState() {

		TelephonyManager tm = (TelephonyManager) Wrapper.getActivity()
				.getSystemService(Wrapper.getActivity().TELEPHONY_SERVICE);

		int callstate = tm.getCallState();

		Log.d("CKGame", "callstate " + callstate);

		return callstate;
	}

	public static String getPackageName() {

		Log.d("CKGame", "pack " + Wrapper.getActivity().getPackageName());

		return Wrapper.getActivity().getPackageName();
	}

	public static String getVersionName() {
		String versionName = "0.0.0";
		try {
			versionName = Wrapper.getActivity().getPackageManager()
					.getPackageInfo(Wrapper.getActivity().getPackageName(), 0).versionName;
			Log.d("CKGame", "VersionName " + versionName);
		} catch (NameNotFoundException e) {
			Log.e("CKGame", "getVersionName error", e);
		}
		return versionName;
	}

	public static int getVersionCode() {
		int versionCode = 0;
		try {
			versionCode = Wrapper.getActivity().getPackageManager()
					.getPackageInfo(Wrapper.getActivity().getPackageName(), 0).versionCode;
			Log.d("CKGame", "VersionCode " + versionCode);
		} catch (NameNotFoundException e) {
			Log.e("CKGame", "getVersionCode error", e);
		}
		return versionCode;
	}

	public static String getLocaleLanguage() {
		java.util.Locale locale = java.util.Locale.getDefault();
		String languageName = locale.getLanguage() + "_" + locale.getCountry();
		return languageName;
	}

	public static String getLocalMacAddress() {
		String macAdd = null;
		try {
			WifiManager wifi = (WifiManager) Wrapper.getActivity()
					.getSystemService(Wrapper.getActivity().WIFI_SERVICE);
			WifiInfo info = wifi.getConnectionInfo();
			macAdd = info.getMacAddress();
		} catch (Exception e) {
			e.printStackTrace();
		}

		return macAdd;
	}

	public static String getImsiNumber() {
		String imsiNumber = null;

		try {
			TelephonyManager phoneMgr = (TelephonyManager) Wrapper
					.getActivity().getSystemService(
							Wrapper.getActivity().TELEPHONY_SERVICE);
			imsiNumber = phoneMgr.getSubscriberId();
		} catch (Exception e) {
			e.printStackTrace();
		}

		return imsiNumber;
	}

	public static String getPhoneNumber() {
		String phoneNumber = null;

		try {
			TelephonyManager phoneMgr = (TelephonyManager) Wrapper
					.getActivity().getSystemService(
							Wrapper.getActivity().TELEPHONY_SERVICE);
			phoneNumber = phoneMgr.getLine1Number();

			if (phoneNumber != null && phoneNumber.length() > 11) {
				phoneNumber = phoneNumber.substring(phoneNumber.length() - 11);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}

		Log.d("CKGame", "phoneNum " + phoneNumber);

		return phoneNumber;
	}

	public static String getDeviceModel() {
		return android.os.Build.MODEL;
	}

	public static int getNetworkStatusCode() {

		ConnectivityManager manager = (ConnectivityManager) Wrapper
				.getActivity().getSystemService(
						Wrapper.getActivity().CONNECTIVITY_SERVICE);

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
		Wrapper.getActivity().startActivity(intent);
	}

	// ===========================================================
	// CKAndroidDeviceEngine
	// ===========================================================

	// ===========================================================
	// MemorySize
	// ===========================================================

	/**
	 * @return 手机内存的可用空间大小
	 */
	public static String getAvailableInternalMemorySize() {

		File path = Environment.getDataDirectory();

		StatFs stat = new StatFs(path.getPath());

		long blockSize = stat.getBlockSize();

		long availableBlocks = stat.getAvailableBlocks();

		return Formatter.formatFileSize(Wrapper.getActivity(), availableBlocks
				* blockSize);

	}

	/**
	 * @return 手机内存的总空间大小
	 */
	public static String getTotalInternalMemorySize() {

		File path = Environment.getDataDirectory();

		StatFs stat = new StatFs(path.getPath());

		long blockSize = stat.getBlockSize();

		long totalBlocks = stat.getBlockCount();

		return Formatter.formatFileSize(Wrapper.getActivity(), totalBlocks
				* blockSize);

	}

	/**
	 * @return sdcard是否存在并具有读/写权限
	 */
	public static boolean externalMemoryAvailable() {

		return Environment.getExternalStorageState().equals(
				Environment.MEDIA_MOUNTED);

	}

	/**
	 * @return 手机sdcard的可用空间大小
	 */
	public static String getAvailableExternalMemorySize() {

		if (externalMemoryAvailable()) {

			File path = Environment.getExternalStorageDirectory();

			StatFs stat = new StatFs(path.getPath());

			long blockSize = stat.getBlockSize();

			long availableBlocks = stat.getAvailableBlocks();

			return Formatter.formatFileSize(Wrapper.getActivity(),
					availableBlocks * blockSize);

		} else {

			return "error";

		}

	}

	/**
	 * @return 手机sdcard的总空间大小
	 */
	public static String getTotalExternalMemorySize() {

		if (externalMemoryAvailable()) {

			File path = Environment.getExternalStorageDirectory();

			StatFs stat = new StatFs(path.getPath());

			long blockSize = stat.getBlockSize();

			long totalBlocks = stat.getBlockCount();

			return Formatter.formatFileSize(Wrapper.getActivity(), totalBlocks
					* blockSize);

		} else {

			return "error";

		}

	}

	/**
	 * @return 手机sdcard的已用空间大小
	 */
	public static String getUsedExternalMemorySize() {

		if (externalMemoryAvailable()) {

			File path = Environment.getExternalStorageDirectory();

			StatFs stat = new StatFs(path.getPath());

			long blockSize = stat.getBlockSize();

			long totalBlocks = stat.getBlockCount();

			long availableBlocks = stat.getAvailableBlocks();

			return Formatter.formatFileSize(Wrapper.getActivity(),
					(totalBlocks - availableBlocks) * blockSize);

		} else {

			return "error";

		}

	}

	public static String getRunningAppProcessInfo() {
		ActivityManager mActivityManager = (ActivityManager) Wrapper
				.getActivity().getSystemService(Context.ACTIVITY_SERVICE);

		// 获得系统里正在运行的所有进程
		List<RunningAppProcessInfo> runningAppProcessesList = mActivityManager
				.getRunningAppProcesses();

		for (RunningAppProcessInfo runningAppProcessInfo : runningAppProcessesList) {
			// 进程ID号
			int pid = runningAppProcessInfo.pid;
			// 用户ID
			int uid = runningAppProcessInfo.uid;
			// 进程名
			String processName = runningAppProcessInfo.processName;
			// 占用的内存
			int[] pids = new int[] { pid };
			Debug.MemoryInfo[] memoryInfo = mActivityManager
					.getProcessMemoryInfo(pids);
			int memorySize = memoryInfo[0].dalvikPrivateDirty;

			Log.e("ck12345", "processName=" + processName + ",pid=" + pid
					+ ",uid=" + uid + ",memorySize=" + memorySize + "kb");
			if (getPackageName().equals(processName)) {
				return "processName=" + processName + ",pid=" + pid + ",uid="
						+ uid + ",memorySize=" + memorySize + "kb";
			}
		}
		return "error";
	}

	// ===========================================================
	// MemorySize
	// ===========================================================

	public static native String httpUtilsGetText(String url);
}
