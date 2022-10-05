package com.example.bialaroza

import android.app.AlertDialog
import android.content.Intent
import android.os.AsyncTask
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v4.content.ContextCompat
import android.support.v4.content.ContextCompat.startActivity
import android.view.View
import android.widget.EditText
import com.example.bialaroza.DB.DBHelper
import com.example.bialaroza.Modal.Message
import kotlinx.android.synthetic.main.activity_send.*
import okhttp3.*
import java.io.IOException
import java.net.URL

class SendActivity : AppCompatActivity() {

    var body : String? = "Coś poszło nie tak Szefie"
    var tittle : String? = "Ojojoj!"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_send)

        button.setOnClickListener {
            AsyncTaskGet(this).execute()
        }

        fab.setOnClickListener { view ->
            val intent = Intent(this, MessageActivity::class.java)
            startActivity(intent)
        }
    }

    class AsyncTaskGet(private var activity: SendActivity?) : AsyncTask<String, String, String>() {
        override fun onPreExecute() {
            super.onPreExecute()
            activity?.MyprogressBar?.visibility = View.VISIBLE
        }

        override fun doInBackground(vararg p0: String?): String {
            val key = activity?.editText?.text

            val loginShared = activity?.getSharedPreferences("com.example.bialaroza.prefs",0)
            val userLogin = loginShared!!.getString("userLogin", "0")

            val url = "http://hufiecgniezno.pl/addMessage.php?id="+userLogin+"&k="+key+"&m=add"

            var tittle = "Zapamiętaj!"
            var body = URL(url).readText()
            if(body == "error") {
                body =
                    "Lorem ipsum dolor sit amet, consectetur adipiscing elit. In blandit bibendum erat in gravida. Phasellus pretium diam eget felis gravida, vitae facilisis augue varius. Phasellus vitae lorem a risus euismod bibendum. Suspendisse molestie metus pulvinar, rhoncus risus nec, lacinia velit. Cras quis metus porttitor arcu aliquam hendrerit sit amet viverra augue."
                tittle = "Nie wiem czy to w czymś pomoże"
            } else {
                val db = DBHelper(activity!!.applicationContext)
                val kk = key.toString()

                if(db.testOne(kk)) {
                    val message = Message(
                        0,
                        body,
                        "manual",
                        kk
                    )
                    db.addMessage(message)
                }else{
                    tittle = "Juz masz takową informację"
                }
            }

            return tittle+"|"+body
        }

        override fun onPostExecute(result: String?) {
            super.onPostExecute(result)
            activity?.MyprogressBar?.visibility = View.INVISIBLE

            val data = result?.split("\\|".toRegex())
            val body = data!![1]
            val tittle = data!![0]

            val builder = AlertDialog.Builder(activity)

            builder.setTitle(tittle)

            builder.setMessage(body)

            builder.setPositiveButton("OK"){dialog, which ->
            }

            val dialog: AlertDialog = builder.create()
            dialog.show()
        }
    }





}
/*
    inner class AsyncTaskHandleJson : AsyncTask<String, String, String>() {
        override fun doInBackground(vararg url: String?): String {
            var text: String
            val connection = URL(url[0]).openConnection() as HttpURLConnection
            try{
                connection.connect()
                text = connection.inputStream.use {it.reader().use{reader -> reader.readText()}}
            }finally {
                connection.disconnect()
            }
            return text
        }
    }*/

