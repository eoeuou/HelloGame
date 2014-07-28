package org.cocos2dx.ckbase.utils;

import java.util.ArrayList;

import org.cocos2dx.ckbase.Wrapper;

import android.content.Context;
import android.net.NetworkInfo;

public class CKNetworkManager {

	public static ArrayList<CKNetworkListener> mListeners = new ArrayList<CKNetworkListener>();

	public static void completeConnectedTask(Context context, NetworkInfo info) {
		for (CKNetworkListener listener : mListeners) {
			listener.onConnected(context, info);
		}
		Wrapper.showToast("completeConnectedTask");
	}

	public static void completeUnConnectedTask(Context context, NetworkInfo info) {
		for (CKNetworkListener listener : mListeners) {
			listener.onUnConnected(context, info);
		}
		Wrapper.showToast("completeUnConnectedTask");
	}

	public static void registerListener(CKNetworkListener listener) {
		if (!mListeners.contains(listener)) {
			mListeners.add(listener);
		}
	}

	public static interface CKNetworkListener {
		public void onConnected(Context context, NetworkInfo info);

		public void onUnConnected(Context context, NetworkInfo info);
	};
}
