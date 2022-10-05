package com.example.clickupbutpoor.adapters

import android.content.Context
import android.content.Intent
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.RecyclerView
import com.example.clickupbutpoor.models.Post
import com.example.clickupbutpoor.R
import com.example.clickupbutpoor.activities.CommentsActivity
import com.example.clickupbutpoor.activities.UserViewActivity

class PostAdapter: RecyclerView.Adapter<PostAdapter.PostViewHolder>() {

    private var postList: ArrayList<Post> = ArrayList()

    fun addItems(items : ArrayList<Post>) {
        this.postList = items
        notifyDataSetChanged()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int) = PostViewHolder (
        LayoutInflater.from(parent.context).inflate(R.layout.post_list_item, parent, false)
    )

    override fun onBindViewHolder(holder: PostViewHolder, position: Int) {
        val post = postList[position]
        holder.bindView(post)
    }

    override fun getItemCount(): Int {
        return postList.size
    }

    class PostViewHolder(var view: View): RecyclerView.ViewHolder(view) {
        private var title = view.findViewById<TextView>(R.id.postListTitle)
        private var body = view.findViewById<TextView>(R.id.postListBody)
        private lateinit var context: Context
        val viewCommentsButton = view.findViewById<Button>(R.id.viewCommentsButton)

        fun bindView(post: Post) {
            title.text = post.title
            body.text = post.body

            context = super.itemView.context

            viewCommentsButton.setOnClickListener() {
                val intent = Intent(this.context, CommentsActivity::class.java)
                intent.putExtra("postId", post.id)
                intent.putExtra("postTitle", post.title)
                ContextCompat.startActivity(this.context, intent, null)
            }
        }
    }
}