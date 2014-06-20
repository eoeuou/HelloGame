package org.cocos2dx.ckbase;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;

public class CKNotification {
	// ===========================================================
	// CKAndroidNotificationEngine
	// ===========================================================

	public static void showNotification(int id, String title, String message,
			String url) {
		NotificationManager manager = (NotificationManager) Wrapper
				.getActivity().getSystemService(Context.NOTIFICATION_SERVICE);

		int iconId = Wrapper
				.getActivity()
				.getResources()
				.getIdentifier("icon", "drawable",
						Wrapper.getActivity().getPackageName());

		Notification notification = new Notification(iconId, title,
				System.currentTimeMillis());

		notification.defaults = Notification.DEFAULT_SOUND;
		notification.flags = Notification.FLAG_AUTO_CANCEL;

		Uri uri = Uri.parse(url);
		Intent intent = new Intent(Intent.ACTION_VIEW, uri);

		PendingIntent pendingIntent = PendingIntent.getActivity(
				Wrapper.getActivity(), 0, intent, PendingIntent.FLAG_ONE_SHOT);

		notification.setLatestEventInfo(Wrapper.getActivity(), title, message,
				pendingIntent);

		manager.notify(id, notification);
	}

	public static void cancelNotification(int id) {
		NotificationManager manager = (NotificationManager) Wrapper
				.getActivity().getSystemService(Context.NOTIFICATION_SERVICE);
		manager.cancel(id);
	}

	public static native void dispatchRecieveNotification(int id, String title,
			String message, String url);

	public static native void dispatchClickNotification(int id);
	// ===========================================================
	// CKAndroidNotificationEngine
	// ===========================================================
}
