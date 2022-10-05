package com.example.clickupbutpoor.adapters

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.clickupbutpoor.R
import com.example.clickupbutpoor.models.Comment

class CommentAdapter: RecyclerView.Adapter<CommentAdapter.CommentViewHolder>() {
    private var commentList: ArrayList<Comment> = ArrayList()

    fun addItems(items : ArrayList<Comment>) {
        this.commentList = items
        notifyDataSetChanged()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int) = CommentViewHolder (
        LayoutInflater.from(parent.context).inflate(R.layout.comment_list_item, parent, false)
    )

    override fun onBindViewHolder(holder: CommentViewHolder, position: Int) {
        val post = commentList[position]
        holder.bindView(post)
    }

    override fun getItemCount(): Int {
        return commentList.size
    }

    class CommentViewHolder(var view: View): RecyclerView.ViewHolder(view) {
        private val name = view.findViewById<TextView>(R.id.commentListName)
        private val email = view.findViewById<TextView>(R.id.commentListEmail)
        private val body = view.findViewById<TextView>(R.id.commentListBody)

        fun bindView(post: Comment) {
            name.text = post.name
            email.text = post.email
            body.text = post.body
        }
    }
}