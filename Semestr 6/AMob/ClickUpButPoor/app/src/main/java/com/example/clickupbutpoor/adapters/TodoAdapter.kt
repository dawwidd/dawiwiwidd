package com.example.clickupbutpoor.adapters

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.clickupbutpoor.R
import com.example.clickupbutpoor.models.Todo

class TodoAdapter: RecyclerView.Adapter<TodoAdapter.TodoViewHolder>() {

    private var todoList: ArrayList<Todo> = ArrayList()

    fun addItems(items : ArrayList<Todo>) {
        this.todoList = items
        notifyDataSetChanged()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int) = TodoViewHolder (
        LayoutInflater.from(parent.context).inflate(R.layout.todo_list_item, parent, false)
    )

    override fun onBindViewHolder(holder: TodoViewHolder, position: Int) {
        val todo = todoList[position]
        holder.bindView(todo)
    }

    override fun getItemCount(): Int {
        return todoList.size
    }

    class TodoViewHolder(var view: View): RecyclerView.ViewHolder(view) {
        private var title = view.findViewById<TextView>(R.id.todoListTitle)
        private var completed = view.findViewById<TextView>(R.id.todoListCompleted)

        fun bindView(todo: Todo) {
            title.text = todo.title
            completed.text = todo.completed.toString()
        }
    }
}