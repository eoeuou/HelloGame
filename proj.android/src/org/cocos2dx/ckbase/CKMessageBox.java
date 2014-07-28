package org.cocos2dx.ckbase;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class CKMessageBox {

	private static final int HANDLER_CREATE_DIALOG = 1;
	private static final int HANDLER_SHOW_DIALOG = 2;
	private static final int HANDLER_HIDE_DIALOG = 3;
	private static final int HANDLER_SET_DIALOG_BUTTON = 4;

	private static AlertDialog m_dialog = null;

	private static native void onNativeButtonClick(int which);

	private static Handler m_handler = new Handler(Wrapper.getActivity()
			.getMainLooper()) {
		public void handleMessage(android.os.Message msg) {
			switch (msg.what) {
			case HANDLER_CREATE_DIALOG:
				DialogMessage dialogInfo = (DialogMessage) msg.obj;
				create(dialogInfo.title, dialogInfo.message);
				break;
			case HANDLER_SHOW_DIALOG:
				show();
				break;
			case HANDLER_HIDE_DIALOG:
				hide();
				break;
			case HANDLER_SET_DIALOG_BUTTON:
				ButtonMessage btnMsg = (ButtonMessage) msg.obj;
				setButton(btnMsg.which, btnMsg.text);
				break;
			default:
				break;
			}
		};
	};

	public static void createDialog(String title, String message) {
		Message msg = m_handler.obtainMessage(HANDLER_CREATE_DIALOG);
		msg.obj = new DialogMessage(title, message);
		m_handler.sendMessage(msg);
	}

	public static void showDialog() {
		Message msg = m_handler.obtainMessage(HANDLER_SHOW_DIALOG);
		m_handler.sendMessage(msg);
	}

	public static void hideDialog() {
		Message msg = m_handler.obtainMessage(HANDLER_HIDE_DIALOG);
		m_handler.sendMessage(msg);
	}

	public static void setDialogButton(int which, String text) {
		Message msg = m_handler.obtainMessage(HANDLER_SET_DIALOG_BUTTON);
		msg.obj = new ButtonMessage(which, text);
		m_handler.sendMessage(msg);
	}

	private static final DialogInterface.OnClickListener m_buttonClickListener = new DialogInterface.OnClickListener() {
		public void onClick(DialogInterface dialog, int which) {
			onNativeButtonClick(which);
		}
	};

	private static void create(String title, String message) {
		if (m_dialog == null) {
			m_dialog = new AlertDialog.Builder(Wrapper.getActivity()).create();
		}
		m_dialog.setTitle(title);
		m_dialog.setMessage(message);
		m_dialog.setCancelable(true);
	}

	private static void setButton(int which, String text) {
		Log.i("ckgame", "CKMessageBox setButton which=" + which + "text=" + text);
		m_dialog.setButton(which, text, m_buttonClickListener);
	}

	private static void show() {
		Log.i("ckgame", "CKMessageBox show");
		m_dialog.show();
	}

	private static void hide() {
		Log.i("ckgame", "CKMessageBox hide");
		m_dialog.dismiss();
		m_dialog = null;
	}

	static class DialogMessage {
		public String title;
		public String message;

		public DialogMessage(String titleString, String messageString) {
			this.title = titleString;
			this.message = messageString;
		}
	}

	static class ButtonMessage {
		public int which;
		public String text;

		public ButtonMessage(int which, String text) {
			this.which = which;
			this.text = text;
		}
	}
}
