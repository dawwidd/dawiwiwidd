package com.example.clickupbutpoor.api

import com.example.clickupbutpoor.models.Comment
import com.example.clickupbutpoor.models.Post
import com.example.clickupbutpoor.models.Todo
import com.example.clickupbutpoor.models.User
import retrofit2.Call
import retrofit2.http.GET
import retrofit2.http.Query

interface ApiService {

    @GET("/users")
    fun getUsers() : Call<ArrayList<User>>

    @GET("/todos")
    fun getTodos(@Query("userId") userId : Int) : Call<ArrayList<Todo>>

    @GET("/posts")
    fun getPosts(@Query("userId") userId : Int) : Call<ArrayList<Post>>

    @GET("/comments")
    fun getComments(@Query("postId") postId : Int) : Call<ArrayList<Comment>>
}