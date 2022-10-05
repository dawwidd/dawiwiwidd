package com.example.joggingapp.fragments

import android.annotation.SuppressLint
import android.os.Bundle
import android.telephony.SmsManager
import android.util.Log
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.fragment.app.FragmentTransaction
import com.example.joggingapp.R
import com.example.joggingapp.services.ApiService
import com.example.joggingapp.services.ServiceGenerator
import com.example.joggingapp.models.Track
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response

class TrackDetailsFragment : Fragment() {

    private lateinit var track: Track
    private var trackId = 0
    private var loggedInUserId = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        if (savedInstanceState == null) {
            val stopperFragment = StopperFragment()
            stopperFragment.loggedInUserId = loggedInUserId
            stopperFragment.trackId = trackId

            var transaction = childFragmentManager.beginTransaction()
            transaction.add(R.id.stopperContainer, stopperFragment)
            transaction.addToBackStack(null)
            transaction.setTransition(FragmentTransaction.TRANSIT_FRAGMENT_FADE)
            transaction.commit()
        }
        else {
            trackId = savedInstanceState.getInt("trackId")
            loggedInUserId = savedInstanceState.getInt("loggedInUserId")
            this.setTrack(trackId)
            this.setLoggedInUserId(loggedInUserId)
        }
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        val view = inflater.inflate(R.layout.fragment_track_details, container, false)

//        view.isFocusable = true
//        view.isClickable = true


        return view
    }

    override fun onSaveInstanceState(savedInstanceState: Bundle) {
        savedInstanceState.putInt("trackId", trackId)
        savedInstanceState.putInt("loggedInUserId", loggedInUserId)
    }

    fun setTrack(trackId: Int) {
        this.trackId = trackId
        val serviceGenerator = ServiceGenerator().buildService(ApiService::class.java)
        val call = serviceGenerator.getTrackById(trackId)

        call.enqueue(object : Callback<Track> {
            @SuppressLint("SetTextI18n")
            override fun onResponse(
                call: Call<Track>,
                response: Response<Track>
            ) {
                if (response.isSuccessful) {
                    track = response.body()!!

                    if(view != null) {
                        val trackNameTV = view?.findViewById<TextView>(R.id.trackDetailsTrackName)
                        val trackLengthTV = view?.findViewById<TextView>(R.id.trackDetailsTrackLength)
                        val trackDifficultyTV = view?.findViewById<TextView>(R.id.trackDetailsTrackDifficulty)
                        val trackLocalizationTV = view?.findViewById<TextView>(R.id.trackDetailsTrackLocalization)
                        val trackDescriptionTV = view?.findViewById<TextView>(R.id.trackDetailsTrackDescription)

                        trackNameTV?.text = track.name
                        trackLengthTV?.text = "Długość trasy: " + track.length.toString()
                        trackDifficultyTV?.text = "Trudność: " + track.difficulty_name.toString()
                        trackLocalizationTV?.text = "Lokalizacja: " + track.localization_name.toString()
                        trackDescriptionTV?.text = track.description.toString()
                    }
                }
            }

            override fun onFailure(call: Call<Track>, t: Throwable) {
                t.printStackTrace()
                Log.e("error", t.message.toString())
            }
        })
    }

    fun setLoggedInUserId(loggedInUserId: Int) {
        this.loggedInUserId = loggedInUserId
    }
}