package org.cocos2dx.ckbase;

import android.app.Activity;
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

}
