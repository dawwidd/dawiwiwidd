package com.example.clickupbutpoor.models

class Todo {
    var userId: Int = 0
    var id: Int = 0
    var title: String? = null
    var completed: Boolean = false

    constructor()

    constructor(title: String, completed: Boolean) {
        this.title = title
        this.completed = completed

    }
}