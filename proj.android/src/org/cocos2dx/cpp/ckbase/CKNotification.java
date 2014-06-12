package org.cocos2dx.cpp.ckbase;

import android.app.Activity;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;

public class CKNotification {

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
	// CKAndroidNotificationEngine
	// ===========================================================

	public static void showNotification(int id, String title, String message,
			String url) {
		NotificationManager manager = (NotificationManager) sActivity
				.getSystemService(Context.NOTIFICATION_SERVICE);

		int iconId = sActivity.getResources().getIdentifier("icon", "drawable",
				sActivity.getPackageName());

		Notification notification = new Notification(iconId, title,
				System.currentTimeMillis());

		notification.defaults = Notification.DEFAULT_SOUND;
		notification.flags = Notification.FLAG_AUTO_CANCEL;

		Uri uri = Uri.parse(url);
		Intent intent = new Intent(Intent.ACTION_VIEW, uri);

		PendingIntent pendingIntent = PendingIntent.getActivity(sActivity, 0,
				intent, PendingIntent.FLAG_ONE_SHOT);

		notification.setLatestEventInfo(sActivity, title, message,
				pendingIntent);

		manager.notify(id, notification);
	}

	public static void cancelNotification(int id) {
		NotificationManager manager = (NotificationManager) sActivity
				.getSystemService(Context.NOTIFICATION_SERVICE);
		manager.cancel(id);
	}

	public static native void dispatchRecieveNotification(int id, String title, String message,
			String url);
	public static native void dispatchClickNotification(int id);
	// ===========================================================
	// CKAndroidNotificationEngine
	// ===========================================================
}
