package com.example.clickupbutpoor.models

class Post {
    var userId: Int = 0
    var id: Int = 0
    var title: String? = null
    var body: String? = null

    constructor()

    constructor(title: String, body: String) {
        this.title = title
        this.body = body

    }
}