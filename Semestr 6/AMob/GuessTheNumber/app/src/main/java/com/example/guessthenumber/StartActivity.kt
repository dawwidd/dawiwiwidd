package com.example.guessthenumber

import android.content.Intent
import android.database.sqlite.SQLiteDatabase
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView

class StartActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_start)

        val welcomeText = findViewById<TextView>(R.id.welcomeText)
        welcomeText.setText("Guess The Number")

        val thread = Thread() {
            run {
                Thread.sleep(3000)
            }
            runOnUiThread() {
                val intent = Intent(this, SignInActivity::class.java)
                startActivity(intent)
                finish()
            }
        }
        thread.start()
    }
}