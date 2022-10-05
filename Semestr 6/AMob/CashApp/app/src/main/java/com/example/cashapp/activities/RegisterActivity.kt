package com.example.cashapp.activities

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.EditText
import androidx.appcompat.widget.Toolbar
import androidx.lifecycle.lifecycleScope
import com.example.cashapp.R
import com.example.cashapp.models.User
import com.example.cashapp.services.RetrofitInstance
import com.example.cashapp.utils.Toaster
import retrofit2.Call
import retrofit2.Callback
import retrofit2.HttpException
import retrofit2.Response
import java.io.IOException

class RegisterActivity : AppCompatActivity() {

    private lateinit var toolbar: androidx.appcompat.widget.Toolbar

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_register)

        setupToolbar()
        val actionBar = supportActionBar
        actionBar?.setDisplayHomeAsUpEnabled(true)

        val registerButton = findViewById<Button>(R.id.registerButton)

        registerButton.setOnClickListener() {
            register()
        }
    }

    private fun register() {
        val editTextFirstName = findViewById<EditText>(R.id.editTextFirstNameR)
        val editTextLastName = findViewById<EditText>(R.id.editTextLastNameR)
        val editTextMail = findViewById<EditText>(R.id.editTextMailR)
        val editTextPassword = findViewById<EditText>(R.id.editTextPasswordR)
        val editTextConfirmPassword = findViewById<EditText>(R.id.editTextConfirmPassword)

        val firstName = editTextFirstName.text.toString()
        val lastName = editTextLastName.text.toString()
        val email = editTextMail.text.toString()
        val password = editTextPassword.text.toString()
        val confirmPassword = editTextConfirmPassword.text.toString()

        val user = User(email, password, firstName, lastName)

        if(firstName.isEmpty() || lastName.isEmpty() || email.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
            Toaster.toast("All the fields have to be filled", applicationContext)
        }
        else if(password != confirmPassword) {
            Toaster.toast("Passwords don't match", applicationContext)
        }
        else {
            lifecycleScope.launchWhenCreated {
                val response = try {
                    RetrofitInstance.api.register(user)
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
                    Toaster.toast("Registered successfully", applicationContext)
                    redirectToLoginActivity()
                }
                else {
                    val errorMessage = response.errorBody()!!.string()
                    Log.e("MainActivity", errorMessage)
                    Toaster.toast(errorMessage, applicationContext)
                }
            }
        }

    }

    private fun redirectToLoginActivity() {
        onBackPressed()
        finish()
    }

    private fun setupToolbar() {
        toolbar = findViewById(R.id.toolbar)
        toolbar.title = resources.getString(R.string.activity_register)
        setSupportActionBar(toolbar)
    }
}