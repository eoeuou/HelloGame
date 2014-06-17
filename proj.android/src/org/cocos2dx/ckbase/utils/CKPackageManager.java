package org.cocos2dx.ckbase.utils;

import java.util.ArrayList;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;

public class CKPackageManager {

	public static ArrayList<CKInstallListener> mListeners = new ArrayList<CKInstallListener>();

	public static void install(Context context,String path){
		Intent intent = new Intent();
		intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK); 
		
        intent.setAction(Intent.ACTION_VIEW);
        intent.addCategory(Intent.CATEGORY_DEFAULT); 
        java.io.File file = new java.io.File(path);
        intent.setDataAndType(Uri.fromFile(file),"application/vnd.android.package-archive");
        
        context.startActivity(intent);
	}
	
	public static void completeInstallTask(Context context,String packName){
		for(CKInstallListener listener : mListeners){
			listener.onInstall(context,packName);
		}
	}
	
	public static void completeUnInstallTask(Context context,String packName){
		for(CKInstallListener listener : mListeners){
			listener.onUnInstall(context,packName);
		}
	}

	public static void registerListener(CKInstallListener listener){
		if(!mListeners.contains(listener)){
			mListeners.add(listener);
		}
	}

	public static interface CKInstallListener{
		public void onInstall(Context context,String packName);
		public void onUnInstall(Context context,String packName);
	};
}
