package com.brgame

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.brgame.message.message
import com.brgame.message.messageAdapter
import kotlin.random.Random

private lateinit var messageAdapter: messageAdapter

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        supportActionBar?.hide()

        messageAdapter = messageAdapter(mutableListOf())

        val messageList = findViewById<RecyclerView>(R.id.messageList)
        messageList.adapter = messageAdapter
        messageList.layoutManager = LinearLayoutManager(this)


        for(a in 1..10) {
            val new = message("Nowe Zadanie $a", "as"+Random.nextInt(10000,20000).toString(), "Waszym zadaniem jest zrobie $a")
            messageAdapter.addMessage(new)
        }
    }
}