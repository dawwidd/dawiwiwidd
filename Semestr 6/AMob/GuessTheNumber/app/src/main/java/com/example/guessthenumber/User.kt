package com.example.guessthenumber

class User {
    var username : String? = null
    var score : Int = 0

    constructor()

    constructor(username: String, score: Int) {
        this.username = username
        this.score = score
    }
}