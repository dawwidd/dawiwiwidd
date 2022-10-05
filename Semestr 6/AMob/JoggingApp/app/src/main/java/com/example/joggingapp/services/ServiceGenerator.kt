package com.example.joggingapp.services

import com.google.gson.GsonBuilder
import okhttp3.OkHttpClient
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory
import retrofit2.converter.scalars.ScalarsConverterFactory
import java.util.*

class ServiceGenerator {
    private val client = OkHttpClient.Builder().build()

    private val gson = GsonBuilder().setDateFormat("EE, dd MM yyyy 'T'HH:mm:ss 'Z'").create()

    private val retrofit = Retrofit.Builder()
        .baseUrl("http://192.168.1.6:5000")
        .addConverterFactory(GsonConverterFactory.create(gson))
        .addConverterFactory(ScalarsConverterFactory.create())
        .client(client)
        .build()

    fun <T> buildService(service: Class<T>): T {
        return retrofit.create(service)
    }
}