package com.example.bialaroza.Adapter

import android.annotation.TargetApi
import android.app.Activity
import android.content.ClipData
import android.content.ClipboardManager
import android.content.Context
import android.content.Context.CLIPBOARD_SERVICE
import android.graphics.Color
import android.graphics.drawable.Drawable
import android.os.Build
import android.support.annotation.RequiresApi
import android.support.v4.content.ContextCompat
import android.support.v4.content.ContextCompat.getDrawable
import android.support.v4.content.ContextCompat.getSystemService
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.BaseAdapter
import android.widget.EditText
import android.widget.Toast
import com.example.bialaroza.Modal.Message
import com.example.bialaroza.R
import kotlinx.android.synthetic.main.content_message.view.*

class ListMessageAdapter(internal var activity:Activity,
                         internal var listMessage:List<Message>):BaseAdapter() {

    internal var inflater:LayoutInflater
    var myClipboard: ClipboardManager? = null
    var myClip: ClipData? = null

    init{
        inflater = activity.getSystemService(Context.LAYOUT_INFLATER_SERVICE) as LayoutInflater
    }

    @TargetApi(Build.VERSION_CODES.LOLLIPOP)
    @RequiresApi(Build.VERSION_CODES.JELLY_BEAN)
    override fun getView(position: Int, convertView: View?, parent: ViewGroup?): View {
        val rowView:View
        rowView = inflater.inflate(R.layout.content_message,null)

        rowView.txt_message.text = listMessage[position].info.toString()
        rowView.txt_key.text = listMessage[position].key.toString()

        if(listMessage[position].type.toString() == "special") {
            rowView.txt_message.background = inflater.context.getDrawable(R.drawable.rounded_message_extra)
            rowView.txt_message.setTextColor(Color.WHITE)
            rowView.txt_key.background = inflater.context.getDrawable(R.drawable.rounded_message_extra)
            rowView.txt_key.setTextColor(Color.WHITE)
        }
        myClipboard = activity.getSystemService(CLIPBOARD_SERVICE) as ClipboardManager?
        rowView.setOnClickListener{
            myClip = ClipData.newPlainText("text", rowView.txt_message.text)
            myClipboard?.setPrimaryClip(myClip)

            Toast.makeText(activity, "Text Copied", Toast.LENGTH_SHORT).show()
        }

        return rowView
    }

    override fun getItem(position: Int): Any {
        return listMessage[position]
    }

    override fun getItemId(position: Int): Long {
        return listMessage[position].id.toLong()
    }

    override fun getCount(): Int {
        return listMessage.size
    }
}