package com.example.clickupbutpoor.adapters

import android.content.Context
import android.content.Intent
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import androidx.core.content.ContextCompat.startActivity
import androidx.recyclerview.widget.RecyclerView
import com.example.clickupbutpoor.R
import com.example.clickupbutpoor.activities.UserViewActivity
import com.example.clickupbutpoor.models.User

class UserAdapter: RecyclerView.Adapter<UserAdapter.UserViewHolder>() {

    private var userList: ArrayList<User> = ArrayList()

    fun addItems(items : ArrayList<User>) {
        this.userList = items
        notifyDataSetChanged()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int) = UserViewHolder (
        LayoutInflater.from(parent.context).inflate(R.layout.user_list_item, parent, false)
    )

    override fun onBindViewHolder(holder: UserViewHolder, position: Int) {
        val user = userList[position]
        holder.bindView(user)
    }

    override fun getItemCount(): Int {
        return userList.size
    }

    class UserViewHolder(var view: View): RecyclerView.ViewHolder(view) {
        private var name = view.findViewById<TextView>(R.id.userListName)
        private var email = view.findViewById<TextView>(R.id.userListEmail)
        private lateinit var context: Context
        val viewUserButton = view.findViewById<Button>(R.id.viewUserButton)

        fun bindView(user: User) {
            name.text = user.name
            email.text = user.email

            context = super.itemView.context

            viewUserButton.setOnClickListener() {
                val intent = Intent(this.context, UserViewActivity::class.java)
                intent.putExtra("userId", user.id)
                intent.putExtra("name", user.name)
                startActivity(this.context, intent, null)
            }
        }
    }
}
