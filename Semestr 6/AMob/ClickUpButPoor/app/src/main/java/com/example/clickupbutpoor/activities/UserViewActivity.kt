package com.example.clickupbutpoor.activities

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.TextView
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.clickupbutpoor.R
import com.example.clickupbutpoor.models.Todo
import com.example.clickupbutpoor.adapters.TodoAdapter
import com.example.clickupbutpoor.models.User
import com.example.clickupbutpoor.api.ApiService
import com.example.clickupbutpoor.api.ServiceGenerator
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response

class UserViewActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_user_view)

        val intent = intent
        val userId = intent.getIntExtra("userId", 0)
        val name = intent.getStringExtra("name")

        val nameTextView = this.findViewById<TextView>(R.id.userNameTextView)
        nameTextView.text = name

        val goBackButton = this.findViewById<Button>(R.id.userViewBackButton)
        val viewUserPostsButton = this.findViewById<Button>(R.id.viewUserPostsButton)

        val todoListView = this.findViewById<RecyclerView>(R.id.todoListView)
        var todoAdapter = TodoAdapter()
        todoListView.layoutManager = LinearLayoutManager(this)
        todoListView?.adapter = todoAdapter

        val serviceGenerator = ServiceGenerator().buildService(ApiService::class.java)
        val call = serviceGenerator.getTodos(userId)

        val todosCountTextView = this.findViewById<TextView>(R.id.todosCountTextView)


        call.enqueue(object : Callback<ArrayList<Todo>> {
            override fun onResponse(
                call: Call<ArrayList<Todo>>,
                response: Response<ArrayList<Todo>>
            ) {
                if (response.isSuccessful) {
                    var todoList = response.body()
                    todoAdapter.addItems(todoList!!)
                    todosCountTextView.text = "Number of tasks: ${todoAdapter.itemCount}"
                }
            }

            override fun onFailure(call: Call<ArrayList<Todo>>, t: Throwable) {
                t.printStackTrace()
                Log.e("error", t.message.toString())
            }
        })

        goBackButton.setOnClickListener() {
            onBackPressed()
            finish()
        }

        viewUserPostsButton.setOnClickListener() {
            val intent = Intent(this, PostListActivity::class.java)
            intent.putExtra("userId", userId)
            startActivity(intent)
        }
    }
}
