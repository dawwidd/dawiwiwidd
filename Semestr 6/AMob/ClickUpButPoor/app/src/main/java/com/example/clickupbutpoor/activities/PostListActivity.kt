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
import com.example.clickupbutpoor.adapters.PostAdapter
import com.example.clickupbutpoor.api.ApiService
import com.example.clickupbutpoor.api.ServiceGenerator
import com.example.clickupbutpoor.models.Post
import org.w3c.dom.Text
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response

class PostListActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_post_list)

        val intent = intent
        val userId = intent.getIntExtra("userId", 0)

        val postListView = this.findViewById<RecyclerView>(R.id.postListView)
        var postAdapter = PostAdapter()
        postListView.layoutManager = LinearLayoutManager(this)
        postListView?.adapter = postAdapter

        val serviceGenerator = ServiceGenerator().buildService(ApiService::class.java)
        val call = serviceGenerator.getPosts(userId)

        val goBackButton = this.findViewById<Button>(R.id.postListBackButton)
        val goToUsersButton = this.findViewById<Button>(R.id.postsGoToUsersButton)
        val postCountTextView = this.findViewById<TextView>(R.id.postCountTextView)

        call.enqueue(object : Callback<ArrayList<Post>> {
            override fun onResponse(
                call: Call<ArrayList<Post>>,
                response: Response<ArrayList<Post>>
            ) {
                if (response.isSuccessful) {
                    var postList = response.body()
                    postAdapter.addItems(postList!!)
                    postCountTextView.text = "Number of posts: ${postAdapter.itemCount}"
                }
            }

            override fun onFailure(call: Call<ArrayList<Post>>, t: Throwable) {
                t.printStackTrace()
                Log.e("error", t.message.toString())
            }

        })

        goBackButton.setOnClickListener() {
            onBackPressed()
            finish()
        }

        goToUsersButton.setOnClickListener() {
            val intent = Intent(this, UserListActivity::class.java)
            startActivity(intent)
            finish()
        }
    }
}