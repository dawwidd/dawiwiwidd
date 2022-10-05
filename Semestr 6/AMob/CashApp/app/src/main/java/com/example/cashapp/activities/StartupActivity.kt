package com.example.cashapp.activities

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.animation.AnimationUtils
import android.widget.ImageView
import com.example.cashapp.R

class StartupActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_startup)

        val imageLogo = findViewById<ImageView>(R.id.imageLogo)
        val animationRotate = AnimationUtils.loadAnimation(applicationContext, R.anim.anim_rotation)
        imageLogo.startAnimation(animationRotate)

        val thread = Thread() {
            run {
                Thread.sleep(4000)
            }

            runOnUiThread() {
                val intent = Intent(this, LoginActivity::class.java)
                startActivity(intent)
                finish()
            }
        }
        thread.start()
    }
}