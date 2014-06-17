package org.cocos2dx.ckbase.utils;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class CKPackageReceiver extends BroadcastReceiver {

	@Override
	public void onReceive(Context context, Intent intent) {

		if (Intent.ACTION_PACKAGE_ADDED.equals(intent.getAction())) {

			String packageName = intent.getDataString();
			CKPackageManager.completeInstallTask(context, packageName);

		} else if (Intent.ACTION_PACKAGE_REMOVED.equals(intent.getAction())) {

			String packageName = intent.getDataString();
			CKPackageManager.completeUnInstallTask(context, packageName);

		}
	}

}
