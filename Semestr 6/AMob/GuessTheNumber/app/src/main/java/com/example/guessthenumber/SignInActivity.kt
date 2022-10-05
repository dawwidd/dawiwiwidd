package com.example.guessthenumber

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast

class SignInActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_sign_in)

        val usernameInput = this.findViewById<EditText>(R.id.usernameInput)
        val passwordInput = this.findViewById<EditText>(R.id.passwordInput)
        val confirmPasswordInput = this.findViewById<EditText>(R.id.confirmPasswordInput)
        val signInButton = this.findViewById<Button>(R.id.signInButton)
        val redirectToLoginButton = this.findViewById<Button>(R.id.redirectToLoginButton)
        val scoreboardButton = this.findViewById<Button>(R.id.scoreboardButtonS)
        val db = DBHelper(applicationContext)

        signInButton.setOnClickListener() {
            var username = usernameInput.text.toString()
            var password = passwordInput.text.toString()
            var confirmPassword = confirmPasswordInput.text.toString()

            if(username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
                toast("All the fields have to be filled")
            }
            else if(password != confirmPassword) {
                toast("Passwords don't match")
            }
            else if(db.checkIfUserExists(username)) {
                toast("Username is already taken")
            }
            else {
                db.createUser(username, password)
                toast("Welcome "+username+"!")
                val intent = Intent(this, MainActivity::class.java)
                intent.putExtra("username", username)
                startActivity(intent)
                finish()
            }
        }

        redirectToLoginButton.setOnClickListener() {
            val intent = Intent(this, LoginActivity::class.java)
            startActivity(intent)
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