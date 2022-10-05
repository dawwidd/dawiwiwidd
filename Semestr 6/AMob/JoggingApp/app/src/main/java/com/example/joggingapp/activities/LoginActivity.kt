package com.example.joggingapp.activities

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.telephony.SmsManager
import android.util.Log
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.appcompat.widget.Toolbar
import com.example.joggingapp.R
import com.example.joggingapp.models.User
import com.example.joggingapp.services.ApiService
import com.example.joggingapp.services.ServiceGenerator
import retrofit2.Callback
import retrofit2.Call
import retrofit2.Response

class LoginActivity : AppCompatActivity(){
    private val serviceGenerator = ServiceGenerator().buildService(ApiService::class.java)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)

        val toolbar = this.findViewById<Toolbar>(R.id.toolbar)
        setSupportActionBar(toolbar)

        val loginButton = findViewById<Button>(R.id.loginButton)
        val noAccountButton = findViewById<Button>(R.id.noAccountButton)

        val smsButton = findViewById<Button>(R.id.sendSmsButton)

        loginButton.setOnClickListener() {
            login()
        }

        noAccountButton.setOnClickListener() {
            redirectToRegisterActivity()
        }

        smsButton.setOnClickListener() {
            var obj = SmsManager.getDefault()
            obj.sendTextMessage("+48502178757", null, "Siema", null, null)
        }
    }

    private fun login() {
        val editTextMail = findViewById<EditText>(R.id.editTextMail)
        val editTextPassword = findViewById<EditText>(R.id.editTextPassword)
        val email = editTextMail.text.toString()
        val password = editTextPassword.text.toString()

        if(email.isEmpty() || password.isEmpty()) {
            toast("All the fields have to be filled")
        }
        else {
            val user = User(email, password)
            val call = serviceGenerator.login(user)

            call.enqueue(object : Callback<User> {
                override fun onResponse(call: Call<User>, response: Response<User>) {
                    if (response.isSuccessful) {
                        val user = response.body()
                        val intent = Intent(applicationContext, MainActivity::class.java)
                        intent.putExtra("loggedInUserId", user?.id)
                        startActivity(intent)
                    }
                    else if(response.code() == 400){
                        toast("User with given email does not have an account yet")
                    }
                    else if(response.code() == 401) {
                        toast("Wrong password")
                    }
                }

                override fun onFailure(call: Call<User>, t: Throwable) {
                    t.printStackTrace()
                    Log.e("error", t.message.toString())
                }

            })
        }
    }

    private fun redirectToRegisterActivity() {
        val intent = Intent(this, RegisterActivity::class.java)
        startActivity(intent)
    }

    fun toast(text: String) {
        Toast.makeText(applicationContext, text, Toast.LENGTH_LONG).show()
    }
}