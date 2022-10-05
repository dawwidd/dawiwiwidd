package com.example.guessthenumber

import android.R.attr.data
import android.os.Bundle
import android.util.Log
import android.widget.ArrayAdapter
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView


class ScoreboardActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_scoreboard)

        val db = DBHelper(applicationContext)

        val goBackButton = this.findViewById<Button>(R.id.goBackButton)

        val scoreboard = this.findViewById<RecyclerView>(R.id.scoreboard)
        scoreboard.layoutManager = LinearLayoutManager(this)
        var userAdapter = UserAdapter()
        scoreboard?.adapter = userAdapter

        val scoreboardList = db.getScoreboard()
        userAdapter.addItems(scoreboardList)

        goBackButton.setOnClickListener() {
            onBackPressed()
        }
    }

    override fun onStop() {
        super.onStop()
        finish()
    }
}