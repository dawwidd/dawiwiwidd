package com.example.cashapp.activities

import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.RadioButton
import android.widget.RadioGroup
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.isVisible
import androidx.lifecycle.lifecycleScope
import com.example.cashapp.R
import com.example.cashapp.databinding.ActivityAddTransactionBinding
import com.example.cashapp.databinding.ActivityMainBinding
import com.example.cashapp.models.Transaction
import com.example.cashapp.services.RetrofitInstance
import com.example.cashapp.utils.Toaster
import retrofit2.HttpException
import java.io.IOException


class AddTransactionActivity : AppCompatActivity() {

    private lateinit var binding: ActivityAddTransactionBinding
    private lateinit var buttonSubmit: Button
    private lateinit var rgp: RadioGroup
    private lateinit var rgTransactionType: RadioGroup
    private lateinit var rbIncome: RadioButton
    private lateinit var rbOutcome: RadioButton
    private lateinit var editTextAmount: EditText
    private lateinit var toolbar: androidx.appcompat.widget.Toolbar

    private var amount: Float? = null
    private var categoryId: Int? = null
    private var userId: Int? = null


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityAddTransactionBinding.inflate(layoutInflater)
        setContentView(binding.root)

        setupToolbar()
        val actionBar = supportActionBar
        actionBar?.setDisplayHomeAsUpEnabled(true)

        buttonSubmit = findViewById(R.id.buttonSubmitTransaction)

        editTextAmount = findViewById(R.id.editTextAmount)

        rgTransactionType = findViewById(R.id.rgTransactionType)
        rbIncome = findViewById(R.id.rbIncome)
        rbOutcome = findViewById(R.id.rbOutcome)

//        lifecycleScope.launchWhenCreated {
//            rgTransactionType = binding.rgTransactionType
//
//            val radioButtonView = layoutInflater.inflate(R.layout.category_button, null, false)
//
////            val rbIncome = radioButtonView.findViewById<RadioButton>(R.id.rbIncome)
////            val rbOutcome = radioButtonView.findViewById<RadioButton>(R.id.rbOutcome)
//        }


        getCategories()
    }

    private fun getCategories() {
        lifecycleScope.launchWhenCreated {
            binding.progressBarAddTransaction.isVisible = true
            val response = try {
                RetrofitInstance.api.getCategories()
            } catch (e: IOException) {
                Log.e("AddTransaction", "IOException, you may not have internet connection")
                binding.progressBarAddTransaction.isVisible = false
                Toaster.toast("You may not have internet connection or server is not available", applicationContext)
                return@launchWhenCreated
            } catch (e: HttpException) {
                Log.e("AddTransaction", "Invalid http response")
                binding.progressBarAddTransaction.isVisible = false
                Toaster.toast("Invalid http response", applicationContext)
                return@launchWhenCreated
            }

            if(response.isSuccessful && response.body() != null && response.body()!!.isNotEmpty()) {
                rgp = binding.rgCategories

                for (category in response.body()!!) {
                    val radioButtonView = layoutInflater.inflate(R.layout.category_button, null, false)
                    val rbn = radioButtonView.findViewById<RadioButton>(R.id.rbCategory)
                    rbn.id = View.generateViewId()
                    rbn.text = category.name
                    rgp.addView(rbn)
                }
            }
            else {
                Log.e("AddTransaction", "Response not successful")
            }
            binding.progressBarAddTransaction.isVisible = false
        }

        buttonSubmit.setOnClickListener() {
            submitTransaction()
        }
    }

    private fun submitTransaction() {
        val selectedRadioButtonId = rgp.checkedRadioButtonId

        if(selectedRadioButtonId != -1 && editTextAmount.text.toString() != "") {
            val selectedRadioButton = findViewById<RadioButton>(selectedRadioButtonId);

            getChosenCategoryId(selectedRadioButton.text.toString())
        }
        else if (editTextAmount.text.toString() != ""){
            Toaster.toast("A category needs to be chosen", applicationContext)
        }
        else if (selectedRadioButtonId != -1) {
            Toaster.toast("Amount needs to be specified", applicationContext)
        }
    }

    private fun getChosenCategoryId(categoryName: String) {

        lifecycleScope.launchWhenCreated {
            val response = try {
                RetrofitInstance.api.getCategories(categoryName)
            } catch (e: IOException) {
                Log.e("AddTransaction", "IOException, you may not have internet connection")
                Toaster.toast("You may not have internet connection or server is not available", applicationContext)
                return@launchWhenCreated
            } catch (e: HttpException) {
                Log.e("AddTransaction", "Invalid http response")
                Toaster.toast("Invalid http response", applicationContext)
                return@launchWhenCreated
            }

            if(response.isSuccessful && response.body() != null && response.body()!!.isNotEmpty()) {
                val category = response.body()!![0]
                categoryId = category.id
                addTransaction()
            }
            else {
                Log.e("AddTransaction", "Response not successful")
                categoryId = 1
            }
        }
    }

    private fun addTransaction() {
        amount = findViewById<EditText>(R.id.editTextAmount).text.toString().toFloat()
        userId = intent.getIntExtra("userId", 0)

        if(rbOutcome.isChecked) {
            amount = -1 * amount!!
        }

        val transaction = Transaction(amount = amount!!, category_id = categoryId!!, user_id = userId!!)

        lifecycleScope.launchWhenCreated {
            val response = try {
                RetrofitInstance.api.addTransaction(transaction)
            } catch (e: IOException) {
                Log.e("AddTransaction", "IOException, you may not have internet connection")
                Toaster.toast("You may not have internet connection or server is not available", applicationContext)
                return@launchWhenCreated
            } catch (e: HttpException) {
                Log.e("AddTransaction", "Invalid http response")
                Toaster.toast("Invalid http response", applicationContext)
                return@launchWhenCreated
            }

            if(response.isSuccessful && response.body() != null) {
                Toaster.toast("Transaction added successfully", applicationContext)
                redirectToMainActivity()
            }
            else {
                val errorMessage = response.errorBody()!!.string()
                Log.e("AddTransaction", errorMessage)
                Toaster.toast(errorMessage, applicationContext)
            }
        }

    }

    private fun redirectToMainActivity() {
        onBackPressed()
        finish()
    }

    private fun setupToolbar() {
        toolbar = findViewById(R.id.toolbar)
        toolbar.title = resources.getString(R.string.activity_add_transaction)
        setSupportActionBar(toolbar)
    }
}