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
import com.example.clickupbutpoor.adapters.CommentAdapter
import com.example.clickupbutpoor.api.ApiService
import com.example.clickupbutpoor.api.ServiceGenerator
import com.example.clickupbutpoor.models.Comment
import org.w3c.dom.Text
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response

class CommentsActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_comments)

        val intent = intent
        val postId = intent.getIntExtra("postId", 0)
        val postTitle = intent.getStringExtra("postTitle")

        val commentListView = this.findViewById<RecyclerView>(R.id.commentListView)
        var commentAdapter = CommentAdapter()
        commentListView.layoutManager = LinearLayoutManager(this)
        commentListView?.adapter = commentAdapter

        val serviceGenerator = ServiceGenerator().buildService(ApiService::class.java)
        val call = serviceGenerator.getComments(postId)

        val goToUsersButton = this.findViewById<Button>(R.id.commentsGoToUsersButton)
        val goBackButton = this.findViewById<Button>(R.id.commentGoBackButton)
        val postTitleTextView = this.findViewById<TextView>(R.id.postTitleTextView)
        postTitleTextView.text = postTitle
        val commentsCountTextView = this.findViewById<TextView>(R.id.commentsCountTextView)

        call.enqueue(object : Callback<ArrayList<Comment>> {
            override fun onResponse(
                call: Call<ArrayList<Comment>>,
                response: Response<ArrayList<Comment>>
            ) {
                if (response.isSuccessful) {
                    var commentList = response.body()
                    commentAdapter.addItems(commentList!!)
                    commentsCountTextView.text = "Number of comments: ${commentAdapter.itemCount}"
                }
            }

            override fun onFailure(call: Call<ArrayList<Comment>>, t: Throwable) {
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