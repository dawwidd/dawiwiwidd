package com.example.cashapp.utils

import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.telephony.SmsManager
import android.util.Log
import com.example.cashapp.R
import com.example.cashapp.activities.ScheduleSmsActivity

class SmsScheduler : BroadcastReceiver() {

    companion object {
        lateinit var phoneNumber: String
    }

    override fun onReceive(context: Context?, intent: Intent?) {
        Toaster.toast("Sms has been sent to number: $phoneNumber", context!!)
        val obj = SmsManager.getDefault()
        val msg = context.resources.getString(R.string.sms_reminder)
        obj.sendTextMessage(phoneNumber, null, msg, null, null)
    }
}