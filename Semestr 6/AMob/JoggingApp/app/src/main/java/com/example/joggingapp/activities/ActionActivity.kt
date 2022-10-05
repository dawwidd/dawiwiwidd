package com.example.joggingapp.activities

import androidx.appcompat.app.AppCompatActivity
import com.example.joggingapp.R
import android.os.Bundle
import androidx.appcompat.widget.Toolbar

class ActionActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_action)

        val toolbar = this.findViewById<Toolbar>(R.id.toolbar)
        setSupportActionBar(toolbar)
        val actionBar = supportActionBar
        actionBar?.setDisplayHomeAsUpEnabled(true)
    }
}