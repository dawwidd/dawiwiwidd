package com.example.guessthenumber

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast

class LoginActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login_screen)

        val usernameLoginInput = this.findViewById<EditText>(R.id.usernameLoginInput)
        val passwordLoginInput = this.findViewById<EditText>(R.id.passwordLoginInput)
        val loginButton = this.findViewById<Button>(R.id.loginButton)
        val scoreboardButton = this.findViewById<Button>(R.id.scoreboardButtonL)
        val db = DBHelper(applicationContext)

        loginButton.setOnClickListener() {
            var username = usernameLoginInput.text.toString()
            var password = passwordLoginInput.text.toString()

            if(db.checkPassword(username, password)) {
                toast("Welcome back $username!")
                val intent = Intent(this, MainActivity::class.java)
                intent.putExtra("username", username)
                startActivity(intent)
                finish()
            }
            else {
                toast("Wrong username or password")
            }
        }

        scoreboardButton.setOnClickListener() {
            val intent = Intent(this, ScoreboardActivity::class.java)
            startActivity(intent)
        }
    }

    fun toast(text: String) {
        Toast.makeText(applicationContext, text, Toast.LENGTH_LONG).show()
    }
}