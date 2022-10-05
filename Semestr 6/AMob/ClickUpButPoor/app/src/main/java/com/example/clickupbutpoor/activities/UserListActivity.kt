package com.example.clickupbutpoor.activities

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.clickupbutpoor.R
import com.example.clickupbutpoor.models.User
import com.example.clickupbutpoor.adapters.UserAdapter
import com.example.clickupbutpoor.api.ApiService
import com.example.clickupbutpoor.api.ServiceGenerator
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response

class UserListActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_user_list)

        val userListView = this.findViewById<RecyclerView>(R.id.userListView)
        userListView.layoutManager = LinearLayoutManager(this)
        var userAdapter = UserAdapter()
        userListView?.adapter = userAdapter

        val serviceGenerator = ServiceGenerator().buildService(ApiService::class.java)
        val call = serviceGenerator.getUsers()

        call.enqueue(object : Callback<ArrayList<User>> {
            override fun onResponse(
                call: Call<ArrayList<User>>,
                response: Response<ArrayList<User>>
            ) {
                if (response.isSuccessful) {
                    var userList = response.body()
                    userAdapter.addItems(userList!!)
                }
            }

            override fun onFailure(call: Call<ArrayList<User>>, t: Throwable) {
                t.printStackTrace()
                Log.e("error", t.message.toString())
            }

        })




    }
}
