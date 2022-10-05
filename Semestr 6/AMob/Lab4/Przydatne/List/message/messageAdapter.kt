package com.brgame.message

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.brgame.R


class messageAdapter(
    private val messages: MutableList<message>
) : RecyclerView.Adapter<messageAdapter.messageViewHolder>() {
    class messageViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView){
        val title = itemView.findViewById<TextView>(R.id.messageTittle)
        val message = itemView.findViewById<TextView>(R.id.messageContent)
        val code = itemView.findViewById<TextView>(R.id.messageCode)

        fun bind(curMessage: message){
            title.text = curMessage.title
            message.text = curMessage.mess
            code.text = curMessage.code
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): messageViewHolder {
        return messageViewHolder(
            LayoutInflater.from(parent.context).inflate(R.layout.item_message, parent, false)
        )
    }

    fun addMessage(message: message) {
        messages.add(message)
        notifyItemInserted(messages.size - 1)
    }

    override fun onBindViewHolder(holder: messageViewHolder, position: Int) {
        val curMessage = messages[position]
        holder.bind(curMessage)
    }

    override fun getItemCount(): Int {
        return messages.size
    }
}