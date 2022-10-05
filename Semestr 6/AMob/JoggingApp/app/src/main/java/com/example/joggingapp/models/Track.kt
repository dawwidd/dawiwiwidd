package com.example.joggingapp.models

class Track {
    var id: Int = 0
    var name: String? = null
    var description: String? = null
    var length: Float? = 0.0f
    var difficulty_id: Int = 0
    var difficulty_name: String? = null
    var localization_id: Int = 0
    var localization_name: String? = null


    constructor()

    constructor(name: String, length: Float) {
        this.name = name
        this.length = length
    }

    companion object {
        var trackList = listOf<Track>(
            Track("Trasa 0", 9.0f),
            Track("Trasa 1", 8.0f),
            Track("Trasa 2", 7.0f),
            Track("Trasa 3", 6.0f),
            Track("Trasa 4", 5.0f)
        )
    }
}