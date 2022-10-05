package com.example.joggingapp.fragments

import android.annotation.SuppressLint
import android.content.Intent
import android.os.Bundle
import android.os.Handler
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import androidx.fragment.app.Fragment
import com.example.joggingapp.R
import com.example.joggingapp.activities.LoginActivity
import com.example.joggingapp.models.Run
import com.example.joggingapp.models.User
import com.example.joggingapp.services.ApiService
import com.example.joggingapp.services.ServiceGenerator
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response
import java.util.concurrent.TimeUnit


class StopperFragment : Fragment(), View.OnClickListener {

    var time = 0
    var running: Boolean = false
    var wasRunning: Boolean = false

    var loggedInUserId: Int = 0
    var trackId: Int = 0

    var latestRunTime: Int = 0
    var personalBestRunTime: Int = 0

    val serviceGenerator = ServiceGenerator().buildService(ApiService::class.java)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        if (savedInstanceState != null) {
            time = savedInstanceState.getInt("time")
            running = savedInstanceState.getBoolean("running")
            wasRunning = savedInstanceState.getBoolean("wasRunning")
            trackId = savedInstanceState.getInt("trackId")
            loggedInUserId = savedInstanceState.getInt("loggedInUserId")
        }
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?,savedInstanceState: Bundle?): View? {
        var layout = inflater.inflate(R.layout.fragment_stopper, container, false)

        runStopper(layout)

        val startButton = layout.findViewById<Button>(R.id.startButton)
        val stopButton = layout.findViewById<Button>(R.id.stopButton)
        val resetButton = layout.findViewById<Button>(R.id.resetButton)
        val saveButton = layout.findViewById<Button>(R.id.saveRunButton)



        startButton?.setOnClickListener(this)
        stopButton?.setOnClickListener(this)
        resetButton?.setOnClickListener(this)
        saveButton?.setOnClickListener(this)

        getLatestRunTime()
        getPersonalBestRunTime()

        return layout
    }

    override fun onPause() {
        super.onPause()
        wasRunning = running
        running = false
    }

    override fun onResume() {
        super.onResume()
        if(wasRunning) {
            running = true
        }
    }

    override fun onSaveInstanceState(savedInstanceState: Bundle) {
        savedInstanceState.putInt("time", time)
        savedInstanceState.putBoolean("running", running)
        savedInstanceState.putBoolean("wasRunning", wasRunning)
        savedInstanceState.putInt("trackId", trackId)
        savedInstanceState.putInt("loggedInUserId", loggedInUserId)
    }

    private fun runStopper(view: View) {
        val timeTV = view.findViewById<TextView>(R.id.time_view)
        val handler = Handler()
        handler.post(object : Runnable {
            override fun run() {
                val hours: Int = time / 3600
                val minutes: Int = time % 3600 / 60
                val secs: Int = time % 60
                val clockTime = String.format("%d:%02d:%02d", hours, minutes, secs)
                timeTV.text = clockTime
                if (running) {
                    time++
                }
                handler.postDelayed(this, 1000)
            }
        })
    }

    override fun onClick(view: View) {
        if (view.id == R.id.startButton) {
            onClickStart()
        }
        else if (view.id == R.id.stopButton) {
            onClickStop()
        }
        else if (view.id == R.id.resetButton) {
            onClickReset()
        }
        else if (view.id == R.id.saveRunButton) {
            saveRun()
        }
    }

    private fun onClickStart() {
        running = true
    }

    private fun onClickStop() {
        running = false
    }

    private fun onClickReset() {
        running = false
        time = 0
    }

    private fun saveRun() {

        val run = Run(loggedInUserId, trackId, time)
        val call = serviceGenerator.saveUserRun(run)

        call.enqueue(object : Callback<Run> {
            override fun onResponse(call: Call<Run>, response: Response<Run>) {
                if (response.isSuccessful) {
                    val res = response.body()
                    getPersonalBestRunTime()
                    getLatestRunTime()
                }
            }

            override fun onFailure(call: Call<Run>, t: Throwable) {
                t.printStackTrace()
                Log.e("error", t.message.toString())
            }

        })
    }

    private fun getPersonalBestRunTime() {
        val call = serviceGenerator.getPersonalBestUserRun(trackId, loggedInUserId)

        call.enqueue(object : Callback<Run> {
//            val personalBestRunTextView = view?.findViewById<TextView>(R.id.personalBestTextView)

            @SuppressLint("SetTextI18n")
            override fun onResponse(call: Call<Run>, response: Response<Run>) {
                if (response.isSuccessful) {
                    val res = response.body()
                    personalBestRunTime = res!!.time
                    val hours: Int = personalBestRunTime / 3600
                    val minutes: Int = personalBestRunTime % 3600 / 60
                    val secs: Int = personalBestRunTime % 60
                    val clockTime = String.format("%d:%02d:%02d", hours, minutes, secs)
                    val personalBestRunDate = res!!.date

                    val personalBestRunTextView = view?.findViewById<TextView>(R.id.personalBestTextView)
                    personalBestRunTextView?.text = "Best run: " + clockTime + ", on " + personalBestRunDate
                }
                else if(response.code() == 401) {
                    val personalBestRunTextView = view?.findViewById<TextView>(R.id.personalBestTextView)
                    personalBestRunTextView?.text = "------"
                }
            }

            override fun onFailure(call: Call<Run>, t: Throwable) {
                t.printStackTrace()
                Log.e("error", t.message.toString())
            }

        })
    }

    private fun getLatestRunTime() {
        val call = serviceGenerator.getLatestUserRun(trackId, loggedInUserId)

        call.enqueue(object : Callback<Run> {


            @SuppressLint("SetTextI18n")
            override fun onResponse(call: Call<Run>, response: Response<Run>) {
                if (response.isSuccessful) {
                    val res = response.body()
                    latestRunTime = res!!.time
                    val hours: Int = latestRunTime / 3600
                    val minutes: Int = latestRunTime % 3600 / 60
                    val secs: Int = latestRunTime % 60
                    val clockTime = String.format("%d:%02d:%02d", hours, minutes, secs)
                    val latestRunDate = res!!.date

                    val latestRunTextView = view?.findViewById<TextView>(R.id.latestRunTextView)
                    latestRunTextView?.text = "Latest run: " + clockTime + ", on " + latestRunDate
                }
                else if (response.code() == 401) {
                    val latestRunTextView = view?.findViewById<TextView>(R.id.latestRunTextView)
                    latestRunTextView?.text = "------"
                }
            }

            override fun onFailure(call: Call<Run>, t: Throwable) {
                t.printStackTrace()
                Log.e("error", t.message.toString())
            }

        })
    }

}