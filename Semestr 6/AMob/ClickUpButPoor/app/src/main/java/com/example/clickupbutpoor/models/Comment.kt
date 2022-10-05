package com.example.clickupbutpoor.models

class Comment {
    var postId: Int = 0
    var id: Int = 0
    var name: String? = null
    var email: String? = null
    var body: String? = null

    constructor()

    constructor(name: String, email: String, body: String) {
        this.name = name
        this.email = email
        this.body = body

    }
}