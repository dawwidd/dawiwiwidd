package com.example.joggingapp.services

import com.example.joggingapp.models.Run
import com.example.joggingapp.models.Track
import com.example.joggingapp.models.User
import okhttp3.RequestBody
import okhttp3.Response
import retrofit2.Call
import retrofit2.Callback
import retrofit2.http.*

interface ApiService {

    @GET("/tracks")
    fun getTracks(@Query("difficulty") difficulty_name: String? = null) : Call<ArrayList<Track>>

    @GET("/tracks/{id}")
    fun getTrackById(@Path("id") id: Int) : Call<Track>

    @POST("/login")
    fun login(@Body user: User) : Call<User>

    @POST("/register")
    fun register(@Body user: User) : Call<User>

    @GET("/latest-run")
    fun getLatestUserRun(@Query("trackId") trackId: Int, @Query("userId") userId: Int) : Call<Run>

    @GET("/record")
    fun getPersonalBestUserRun(@Query("trackId") trackId: Int, @Query("userId") userId: Int) : Call<Run>

    @POST("/run")
    fun saveUserRun(@Body run: Run) : Call<Run>

}