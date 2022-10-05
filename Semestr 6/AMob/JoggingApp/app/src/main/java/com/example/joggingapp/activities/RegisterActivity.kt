package com.example.joggingapp.activities

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.appcompat.widget.Toolbar
import com.example.joggingapp.R
import com.example.joggingapp.models.User
import com.example.joggingapp.services.ApiService
import com.example.joggingapp.services.ServiceGenerator
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response

class RegisterActivity : AppCompatActivity() {
    private val serviceGenerator = ServiceGenerator().buildService(ApiService::class.java)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_register)

        val toolbar = this.findViewById<Toolbar>(R.id.toolbar)
        setSupportActionBar(toolbar)

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
        val call = serviceGenerator.register(user)

        if(firstName.isEmpty() || lastName.isEmpty() || email.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
            toast("All the fields have to be filled")
        }
        else if(password != confirmPassword) {
            toast("Passwords don't match")
        }
        else {
            call.enqueue(object : Callback<User> {
                override fun onResponse(call: Call<User>, response: Response<User>) {
                    if (response.isSuccessful) {
                        toast("Successfully created an account")
                        val intent = Intent(applicationContext, LoginActivity::class.java)
                        startActivity(intent)
                    }
                    else if(response.code() == 400){
                        toast("User with given email already has an account")
                    }
                }

                override fun onFailure(call: Call<User>, t: Throwable) {
                    t.printStackTrace()
                    Log.e("error", t.message.toString())
                }

            })
        }

    }

    fun toast(text: String) {
        Toast.makeText(applicationContext, text, Toast.LENGTH_LONG).show()
    }
}