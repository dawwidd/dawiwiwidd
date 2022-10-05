package com.example.cashapp.utils

import android.content.Context
import android.widget.Toast

class Toaster {

    companion object {
        fun toast(text: String, context: Context) {
            val toast = Toast.makeText(context, text, Toast.LENGTH_LONG)
            toast.show()
        }
    }
}