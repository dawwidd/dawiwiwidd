package com.example.cashapp.services

import com.example.cashapp.models.BasicApiResponse
import com.example.cashapp.models.Category
import com.example.cashapp.models.Transaction
import com.example.cashapp.models.User
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response
import retrofit2.http.*

interface ApiService {

    @GET("/transactions")
    suspend fun getUserTransactions(@Query("user_id") user_id: Int = 0) : Response<List<Transaction>>

    @POST("/login")
    suspend fun login(@Body user: User) : Response<BasicApiResponse>

    @POST("/register")
    suspend fun register(@Body user: User) : Response<BasicApiResponse>

    @GET("/categories")
    suspend fun getCategories(@Query("name") name: String? = null) : Response<List<Category>>

    @POST("/transactions")
    suspend fun addTransaction(@Body transaction: Transaction) : Response<BasicApiResponse>

    @DELETE("/transactions")
    suspend fun removeTransaction(@Query("id") id: Int = 0) : Response<BasicApiResponse>
}