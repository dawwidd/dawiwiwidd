package com.example.joggingapp.models

import android.text.format.DateFormat
import java.sql.Date
import java.sql.Timestamp
import java.time.format.DateTimeFormatter
import java.util.*

class Run {
    var id: Int = 0
    var user_id: Int = 0
    var track_id: Int = 0
    var time: Int = 0
    var date: String? = null

    constructor(user_id: Int, track_id: Int, time: Int) {
        this.user_id = user_id
        this.track_id = track_id
        this.time = time
    }
}