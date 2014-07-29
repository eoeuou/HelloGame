package org.cocos2dx.ckbase;

import java.util.List;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.net.Uri;
import android.view.Gravity;
import android.widget.Toast;

public class Wrapper {

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

	public static void showToast(final String text) {
		Wrapper.getActivity().runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Toast toast = new Toast(Wrapper.getActivity());
				toast = Toast.makeText(Wrapper.getActivity(), text,
						Toast.LENGTH_SHORT);
				toast.setGravity(Gravity.BOTTOM, 0, 50);
				toast.show();
			}
		});
	}

	public static void showToast(final String text, final int duration) {
		Wrapper.getActivity().runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Toast toast = new Toast(Wrapper.getActivity());
				toast = Toast.makeText(Wrapper.getActivity(), text, duration);
				toast.setGravity(Gravity.BOTTOM, 0, 50);
				toast.show();
			}
		});
	}

	public static void openUrl(String url) {
		Uri uri = Uri.parse(url);
		Intent intent = new Intent(Intent.ACTION_VIEW, uri);
		Wrapper.getActivity().startActivity(intent);
	}

	public static void install(String path) {
		Intent intent = new Intent();
		intent.setAction(Intent.ACTION_VIEW);
		intent.addCategory(Intent.CATEGORY_DEFAULT);
		java.io.File file = new java.io.File(path);
		intent.setDataAndType(Uri.fromFile(file),
				"application/vnd.android.package-archive");
		Wrapper.getActivity().startActivity(intent);
	}

	public static boolean isInstalled(String packName) {
		Intent intent = Wrapper.getActivity().getPackageManager()
				.getLaunchIntentForPackage(packName);
		boolean installed = intent != null;
		if (!installed) {
			List<PackageInfo> pinfo = Wrapper.getActivity().getPackageManager()
					.getInstalledPackages(0);
			if (pinfo != null) {
				for (PackageInfo p : pinfo) {
					final String pn = p.packageName;
					if (pn.equals(packName)) {
						installed = true;
						break;
					}
				}
			}
		}
		return installed;
	}

}
