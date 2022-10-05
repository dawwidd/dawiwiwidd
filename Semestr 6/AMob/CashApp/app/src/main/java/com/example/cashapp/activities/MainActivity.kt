package com.example.cashapp.activities

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import androidx.core.view.isVisible
import androidx.lifecycle.lifecycleScope
import androidx.recyclerview.widget.LinearLayoutManager
import com.example.cashapp.R
import com.example.cashapp.adapters.TransactionAdapter
import com.example.cashapp.databinding.ActivityMainBinding
import com.example.cashapp.services.RetrofitInstance
import com.example.cashapp.utils.Toaster
import com.google.android.material.floatingactionbutton.FloatingActionButton
import retrofit2.HttpException
import java.io.IOException

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    private lateinit var transactionAdapter: TransactionAdapter
    private lateinit var addTransactionButton: FloatingActionButton
    private lateinit var toolbar: androidx.appcompat.widget.Toolbar

    private var userId: Int = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        setupToolbar()
        val actionBar = supportActionBar
        actionBar?.setDisplayHomeAsUpEnabled(true)

        userId = intent.getIntExtra("userId", 0)

        addTransactionButton = findViewById(R.id.fabAddTransaction)
        addTransactionButton.setOnClickListener() {
            redirectToAddTransactionActivity(userId)
        }

        setupRecyclerView()
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when(item.itemId) {
            R.id.action_action -> {
                val intent = Intent(this, ScheduleSmsActivity::class.java)
                startActivity(intent)
            }
        }
        return super.onOptionsItemSelected(item)
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.menu_main, menu)

        return super.onCreateOptionsMenu(menu)
    }

    override fun onResume() {
        super.onResume()
        setupRecyclerView()
    }

    private fun setupRecyclerView() = binding.rvTransactions.apply {
        transactionAdapter = TransactionAdapter()
        transactionAdapter.setOnItemClickListener(object: TransactionAdapter.OnItemClickListener {
            override fun onDeleteClick(id: Int) {
                removeTransaction(id)
            }
        })
        adapter = transactionAdapter
        layoutManager = LinearLayoutManager(this@MainActivity)
        getTransactions()
    }

    private fun getTransactions() {
        lifecycleScope.launchWhenCreated {
            binding.progressBar.isVisible = true
            binding.noTransactionsAlert.isVisible = false
            val response = try {
                RetrofitInstance.api.getUserTransactions(userId)
            } catch (e: IOException) {
                Log.e("MainActivity", "IOException, you may not have internet connection")
                binding.progressBar.isVisible = false
                Toaster.toast("You may not have internet connection or server is not available", applicationContext)
                return@launchWhenCreated
            } catch (e: HttpException) {
                Log.e("MainActivity", "Invalid http response")
                binding.progressBar.isVisible = false
                Toaster.toast("Invalid http response", applicationContext)
                return@launchWhenCreated
            }

            if(response.isSuccessful && response.body() != null && response.body()!!.isNotEmpty()) {
                transactionAdapter.transactions = response.body()!!
            }
            else if (response.isSuccessful && response.body() != null && response.body()!!.isEmpty()){
                binding.noTransactionsAlert.isVisible = true
            }
            else {
                Log.e("MainActivity", "Response not successful")
            }
            binding.progressBar.isVisible = false
        }
    }

    private fun removeTransaction(id: Int) {
        lifecycleScope.launchWhenCreated {
            val response = try {
                RetrofitInstance.api.removeTransaction(id)
            } catch (e: IOException) {
                Log.e("MainActivity", "IOException, you may not have internet connection")
                binding.progressBar.isVisible = false
                Toaster.toast("You may not have internet connection or server is not available", applicationContext)
                return@launchWhenCreated
            } catch (e: HttpException) {
                Log.e("MainActivity", "Invalid http response")
                binding.progressBar.isVisible = false
                Toaster.toast("Invalid http response", applicationContext)
                return@launchWhenCreated
            }

            if(response.isSuccessful && response.body() != null) {
                setupRecyclerView()
            }
            else {
                Log.e("MainActivity", "Response not successful")
            }
            binding.progressBar.isVisible = false
        }
    }

    private fun redirectToAddTransactionActivity(userId: Int) {
        val intent = Intent(this, AddTransactionActivity::class.java)
        intent.putExtra("userId", userId)
        startActivity(intent)
    }

    private fun setupToolbar() {
        toolbar = findViewById(R.id.toolbar)
        toolbar.title = resources.getString(R.string.activity_main)
        setSupportActionBar(toolbar)
    }
}