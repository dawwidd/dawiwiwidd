package com.example.cashapp.models

data class Transaction (
    var id: Int = 0,
    var amount: Float = 0.0f,
    var date: String? = null,
    var user_id: Int = 0,
    var category_id: Int = 0,
    var category_name: String? = null
)