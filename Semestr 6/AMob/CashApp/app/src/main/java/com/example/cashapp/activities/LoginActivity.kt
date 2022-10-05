package com.example.cashapp.activities

import android.content.Intent
import android.content.SharedPreferences
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.EditText
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.lifecycleScope
import com.example.cashapp.R
import com.example.cashapp.models.User
import com.example.cashapp.services.RetrofitInstance
import com.example.cashapp.utils.Toaster
import retrofit2.HttpException
import java.io.IOException

class LoginActivity : AppCompatActivity() {

    private lateinit var editTextMail: EditText
    private lateinit var editTextPassword: EditText
    private var loginPreferences: SharedPreferences? = null
    private var loginPrefsEditor: SharedPreferences.Editor? = null
    private lateinit var email: String
    private lateinit var password: String
    private lateinit var toolbar: androidx.appcompat.widget.Toolbar

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)

        setupToolbar()

        val loginButton = findViewById<Button>(R.id.loginButton)
        val noAccountButton = findViewById<Button>(R.id.noAccountButton)
        editTextMail = findViewById(R.id.editTextMail)
        editTextPassword = findViewById(R.id.editTextPassword)

        getUserDataFromSharedPreferences()

        loginButton.setOnClickListener() {
            login()
        }

        noAccountButton.setOnClickListener() {
            redirectToRegisterActivity()
        }
    }

    private fun login() {
        email = editTextMail.text.toString()
        password = editTextPassword.text.toString()

        if(email.isEmpty() || password.isEmpty()) {
            Toaster.toast("All the fields have to be filled", applicationContext)
        }
        else {
            val user = User(email, password)

            lifecycleScope.launchWhenCreated {
                val response = try {
                    RetrofitInstance.api.login(user)
                } catch (e: IOException) {
                    Log.e("MainActivity", "IOException, you may not have internet connection")
                    Toaster.toast("You may not have internet connection or server is not available", applicationContext)
                    return@launchWhenCreated
                } catch (e: HttpException) {
                    Log.e("MainActivity", "Invalid http response")
                    Toaster.toast("Invalid http response", applicationContext)
                    return@launchWhenCreated
                }

                if(response.isSuccessful && response.body() != null) {
                    Toaster.toast("Logged in successfully", applicationContext)
                    saveUserDataToSharedPreferences()
                    redirectToMainActivity(response.body()!!.id)
                }
                else {
                    val errorMessage = response.errorBody()!!.string()
                    Log.e("MainActivity", errorMessage)
                    Toaster.toast(errorMessage, applicationContext)
                }
            }
        }
    }

    private fun redirectToRegisterActivity() {
        val intent = Intent(this, RegisterActivity::class.java)
        startActivity(intent)
    }

    private fun redirectToMainActivity(userId: Int) {
        val intent = Intent(this, MainActivity::class.java)
        intent.putExtra("userId", userId)
        startActivity(intent)
        finish()
    }

    private fun getUserDataFromSharedPreferences() {
        loginPreferences = getSharedPreferences("loginPrefs", MODE_PRIVATE)
        loginPrefsEditor = loginPreferences?.edit()
        editTextMail.setText(loginPreferences?.getString("email", ""))
        editTextPassword.setText(loginPreferences?.getString("password", ""))
        email = editTextMail.text.toString()
        password = editTextPassword.text.toString()
    }

    private fun saveUserDataToSharedPreferences() {
        email = editTextMail.text.toString()
        password = editTextPassword.text.toString()
        loginPrefsEditor?.putString("email", email)
        loginPrefsEditor?.putString("password", password)
        loginPrefsEditor?.commit()
    }

    private fun setupToolbar() {
        toolbar = findViewById(R.id.toolbar)
        toolbar.title = resources.getString(R.string.activity_login)
        setSupportActionBar(toolbar)
    }
}