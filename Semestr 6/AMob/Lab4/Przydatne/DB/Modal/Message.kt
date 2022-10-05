package com.example.bialaroza.Modal

class Message {
    var id : Int = 0
    var info : String? = null
    var type : String? = null
    var key : String? = null

    constructor(){}

    constructor(id:Int, info:String,
                type:String, key:String){
        this.id = id
        this.info = info
        this.type = type
        this.key = key
    }
}