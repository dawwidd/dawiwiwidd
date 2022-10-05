package com.example.guessthenumber

import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class UserAdapter: RecyclerView.Adapter<UserAdapter.UserViewHolder>() {

    private var userList: ArrayList<User> = ArrayList()

    fun addItems(items: ArrayList<User>) {
        this.userList = items
        notifyDataSetChanged()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int) = UserViewHolder(
        LayoutInflater.from(parent.context).inflate(R.layout.scoreboard_items, parent, false)
    )

    override fun onBindViewHolder(holder: UserViewHolder, position: Int) {
        val user = userList[position]
        holder.bindView(user)
    }

    override fun getItemCount(): Int {
        return userList.size
    }

    class UserViewHolder(var view: View): RecyclerView.ViewHolder(view){

        private var username = view.findViewById<TextView>(R.id.scoreboardUsername)
        private var score = view.findViewById<TextView>(R.id.scoreboardScore)

        fun bindView(user: User) {
            username.text = user.username
            score.text = user.score.toString()
        }
    }
}