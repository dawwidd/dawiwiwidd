package com.example.cashapp.adapters

import android.annotation.SuppressLint
import android.content.Context
import android.graphics.Color
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.ImageButton
import android.widget.RadioButton
import androidx.core.content.ContextCompat
import androidx.core.view.isVisible
import androidx.lifecycle.lifecycleScope
import androidx.recyclerview.widget.AsyncListDiffer
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.RecyclerView
import com.example.cashapp.R
import com.example.cashapp.databinding.ItemTransactionBinding
import com.example.cashapp.models.Transaction
import com.example.cashapp.services.RetrofitInstance
import com.example.cashapp.utils.Toaster
import retrofit2.HttpException
import java.io.IOException
import java.text.SimpleDateFormat
import kotlin.coroutines.coroutineContext

class TransactionAdapter() : RecyclerView.Adapter<TransactionAdapter.TransactionViewHolder>() {

    private lateinit var listener: OnItemClickListener

    interface OnItemClickListener {
        fun onDeleteClick(id: Int)
    }

    fun setOnItemClickListener(listener: OnItemClickListener) {
        this.listener = listener
    }

    class TransactionViewHolder(val binding: ItemTransactionBinding) : RecyclerView.ViewHolder(binding.root) {

        @SuppressLint("SimpleDateFormat")
        fun bindView(transaction: Transaction, listener: OnItemClickListener) {
            binding.apply {
                tvAmount.text = transaction.amount.toString()
                if(transaction.amount < 0) {
                    tvAmount.setTextColor(ContextCompat.getColor(getContext(), R.color.red));
                }
                var dateFormat = SimpleDateFormat("EEE, dd MMM yyyy hh:mm:ss Z")
                var newDate = dateFormat.parse(transaction.date!!)

                dateFormat = SimpleDateFormat("dd.MM.yyyy")
                var date = dateFormat.format(newDate!!)
                tvDate.text = date
                tvCategoryName.text = transaction.category_name

                val buttonDeleteTransaction = itemView.findViewById<ImageButton>(R.id.buttonDeleteTransaction)

                buttonDeleteTransaction.setOnClickListener() {
                    listener.onDeleteClick(transaction.id)
                }
            }
        }

        fun getContext(): Context {
            return itemView.context;
        }
    }

    private val diffCallback = object : DiffUtil.ItemCallback<Transaction>() {
        override fun areItemsTheSame(oldItem: Transaction, newItem: Transaction): Boolean {
            return oldItem.id == newItem.id
        }

        @SuppressLint("DiffUtilEquals")
        override fun areContentsTheSame(oldItem: Transaction, newItem: Transaction): Boolean {
            return oldItem == newItem
        }
    }

    private val differ = AsyncListDiffer(this, diffCallback)
    var transactions: List<Transaction>
        get() = differ.currentList
        set(value) { differ.submitList(value) }

    override fun getItemCount(): Int {
        return transactions.size
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): TransactionViewHolder {
        return TransactionViewHolder(ItemTransactionBinding.inflate(
            LayoutInflater.from(parent.context),
            parent,
            false
        ))
    }

    @SuppressLint("SimpleDateFormat")
    override fun onBindViewHolder(holder: TransactionViewHolder, position: Int) {
        val transaction = transactions[position]
        holder.bindView(transaction, listener)
    }
}