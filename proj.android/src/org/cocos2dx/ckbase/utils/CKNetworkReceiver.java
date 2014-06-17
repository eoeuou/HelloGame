package org.cocos2dx.ckbase.utils;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

public class CKNetworkReceiver extends BroadcastReceiver {

	@Override
	public void onReceive(Context context, Intent intent) {
		String netaction = "android.net.conn.CONNECTIVITY_CHANGE";

		if (netaction.equals(intent.getAction())) {

			ConnectivityManager connectivityManager = (ConnectivityManager) context
					.getSystemService(Context.CONNECTIVITY_SERVICE);

			NetworkInfo activeNetInfo = connectivityManager
					.getActiveNetworkInfo();

			if (activeNetInfo != null && activeNetInfo.isConnected()) {
				CKNetworkManager.completeConnectedTask(context, activeNetInfo);
			} else {
				CKNetworkManager
						.completeUnConnectedTask(context, activeNetInfo);
			}
		}
	}
}
