package com.example.joggingapp.fragments

import android.content.Context
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.FrameLayout
import android.widget.ListAdapter
import android.widget.ListView
import androidx.fragment.app.ListFragment
import com.example.joggingapp.R
import com.example.joggingapp.services.ApiService
import com.example.joggingapp.services.ServiceGenerator
import com.example.joggingapp.models.Track
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response


class TrackListFragment : ListFragment() {

    var trackDifficultyName: String? = null
    var loggedInUserId = 0
    lateinit var trackList: List<Track>

    interface Listener {
        fun itemClicked(id: Int)
    }

    private lateinit var listener: Listener

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        if(savedInstanceState != null) {
            trackDifficultyName = savedInstanceState.getString("trackDifficultyName")
            loggedInUserId = savedInstanceState.getInt("loggedInUserId")
        }
    }

    override fun onSaveInstanceState(savedInstanceState: Bundle) {
        savedInstanceState.putString("trackDifficultyName", trackDifficultyName)
        savedInstanceState.putInt("loggedInUserId", loggedInUserId)
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {

        val layout = inflater.inflate(R.layout.fragment_track_list, container, false)

        getTracksFromApi(inflater)

        return layout
    }

    override fun onAttach(context: Context) {
        super.onAttach(context)
        this.listener = context as Listener
    }

    override fun onListItemClick(l: ListView, v: View, position: Int, id: Long) {
//        super.onListItemClick(l, v, position, id)
        var fragmentContainer = activity?.findViewById<FrameLayout>(R.id.fragmentContainer)
        if (fragmentContainer != null) {
            listener.itemClicked(trackList[id.toInt()].id)
        }
        else {
            listener.itemClicked(trackList[id.toInt()].id-1)
        }

    }

    fun getTracksFromApi(inflater: LayoutInflater) {
        val serviceGenerator = ServiceGenerator().buildService(ApiService::class.java)
        val call = serviceGenerator.getTracks(trackDifficultyName)

        call.enqueue(object : Callback<ArrayList<Track>> {
            override fun onResponse(
                call: Call<ArrayList<Track>>,
                response: Response<ArrayList<Track>>
            ) {
                if (response.isSuccessful) {
                    trackList = response.body()!!

                    var trackNames = ArrayList<String>()
                    for(track in trackList as List<Track>) {
                        trackNames.add(track.name!!)
                    }

                    val adapter: Any = ArrayAdapter<Any?>(
                        inflater.context, android.R.layout.simple_list_item_1, trackNames as List<Any?>
                    )
                    listAdapter = adapter as ListAdapter?
                }
            }

            override fun onFailure(call: Call<ArrayList<Track>>, t: Throwable) {
                t.printStackTrace()
                Log.e("error", t.message.toString())
            }

        })
    }
}