package com.example.joggingapp.models

class User {
    var id: Int = 0
    var email: String? = null
    var password: String? = null
    var first_name: String? = null
    var last_name: String? = null

    constructor(email: String, password: String) {
        this.email = email
        this.password = password
    }

    constructor(email: String, password: String, first_name: String, last_name: String) {
        this.email = email
        this.password = password
        this.first_name = first_name
        this.last_name = last_name
    }
}