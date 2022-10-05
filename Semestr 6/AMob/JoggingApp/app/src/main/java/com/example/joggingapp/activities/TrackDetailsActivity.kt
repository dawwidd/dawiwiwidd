package com.example.joggingapp.activities

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.widget.Toolbar
import com.example.joggingapp.R
import com.example.joggingapp.fragments.TrackDetailsFragment


class TrackDetailsActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_track_details)

        val toolbar = this.findViewById<Toolbar>(R.id.toolbar)
        setSupportActionBar(toolbar)

        val actionBar = supportActionBar
        actionBar?.setDisplayHomeAsUpEnabled(true)

        var trackDetailsFragment: TrackDetailsFragment? = supportFragmentManager.findFragmentById(R.id.trackDetailsFragment) as TrackDetailsFragment?

        if (trackDetailsFragment == null) {
            trackDetailsFragment = TrackDetailsFragment()
            supportFragmentManager.beginTransaction()
                .add(R.id.trackDetailsFragment, trackDetailsFragment)
                .commit()
        }
//
        val trackId = intent.extras?.get(TRACK_ID_KEY) as Int
        val loggedInUserId = intent.extras?.get("loggedInUserId") as Int

        trackDetailsFragment.setTrack(trackId + 1)
        trackDetailsFragment.setLoggedInUserId(loggedInUserId)
    }

    companion object {
        val TRACK_ID_KEY = "trackId"
    }
}