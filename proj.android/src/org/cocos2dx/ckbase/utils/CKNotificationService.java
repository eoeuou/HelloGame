package org.cocos2dx.ckbase.utils;

import org.cocos2dx.ckbase.CKGameHelper;
import org.cocos2dx.ckbase.CKNotification;
import org.json.JSONObject;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Binder;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.util.Log;

public class CKNotificationService extends Service {

	private static final String ACTION_CLICK = "com.ckgame.CLICK_NOTIFICATION";
	private static final String ACTION_PULL = "com.ckgame.PULL_NOTIFICATION";

	private static final String PULL_URL = "http://192.168.3.109:8000/pull_message/?code=%s";
	private static final String CLICK_URL = "http://192.168.3.109:8000/click_message/?code=%s";
	private static final String NOTIFICATION_ID = "m_id";

	private native String getUserToken();
	
	private native void onRecievedNotification(int id, String title,
			String message, String url);

	private native void onClickedNotification(int id);

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		Log.i("ckgame", "NotificationService start");

		if (intent != null && ACTION_CLICK.equals(intent.getAction())) {
			Bundle bundle = intent.getExtras();

			if (bundle.containsKey(NOTIFICATION_ID)) {
				final int id = bundle.getInt(NOTIFICATION_ID);
				clickNotification(intent, id);
			} else {
				Log.w("ckgame", "notification id is not set");
			}
		} else {
			pullNotification();
		}

		return START_STICKY;
	}

	@Override
	public IBinder onBind(Intent intent) {
		return mBinder;
	}

	private final IBinder mBinder = new Binder() {
		CKNotificationService getService() {
			return CKNotificationService.this;
		}
	};

	static void startDelay(final Context context, int delay) {
		Handler handler = new Handler() {
			public void handleMessage(Message msg) {
				Intent intent = new Intent(context, CKNotificationService.class);
				context.startService(intent);
			}
		};
		handler.sendEmptyMessageDelayed(0, delay);
	}

	private void pullNotification(){
		final String url = String.format(PULL_URL,getUserToken());

		Log.i("ckgame", url);

		String response = CKGameHelper.httpUtilsGetText(url);

		Log.d("ckgame", "response=" + response);

		try {
			JSONObject json = new JSONObject(response);
			
			final int id = json.getInt("id");
			final String title = json.getString("title");
			final String message = json.getString("message");
			final String uri = json.getString("url");
			
			onRecievedNotification(id,title,message,uri);

			CKNotification.showNotification(id, title, message, uri);
		} catch (Exception e) {
			Log.e("ckgame", e.getMessage(), e);
		}
	}
	
	private void clickNotification(Intent intent,int id){	
		
		onClickedNotification(id);
		
		final Uri uri = intent.getData();			
		if(uri!=null){
			intent = new Intent(getApplication(),CKNotificationService.class);
			intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK); 
			intent.setData(uri); 
			startActivity(intent);
		}
		
		final String url = String.format(CLICK_URL,getUserToken()+"&m="+id);
		Log.i("ckgame", url);
		String response = CKGameHelper.httpUtilsGetText(url);
		
		try {
			JSONObject json = new JSONObject(response);
			final int error = json.getInt("err");
			if(error==0){
				CKNotification.cancelNotification(id);
			}else{
				Log.e("ckgame",  json.getString("errMsg"));
			}
		}catch (Exception e) {
			Log.e("ckgame", e.getMessage(), e);
		}
		 
	}
	
}
