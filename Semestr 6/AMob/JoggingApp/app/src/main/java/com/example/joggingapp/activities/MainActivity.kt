package com.example.joggingapp.activities

import android.content.Intent
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.widget.FrameLayout
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.widget.Toolbar
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import androidx.fragment.app.FragmentPagerAdapter
import androidx.fragment.app.FragmentTransaction.TRANSIT_FRAGMENT_FADE
import androidx.viewpager.widget.ViewPager
import com.example.joggingapp.R
import com.example.joggingapp.fragments.TrackDetailsFragment
import com.example.joggingapp.fragments.TrackListFragment
import com.google.android.material.tabs.TabLayout


class MainActivity : AppCompatActivity(), TrackListFragment.Listener{

    var loggedInUserId = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        if(savedInstanceState != null) {
            loggedInUserId = savedInstanceState.getInt("loggedInUserId")
        }

        loggedInUserId = intent.extras?.get("loggedInUserId") as Int

        val toolbar = this.findViewById<Toolbar>(R.id.toolbar)
        setSupportActionBar(toolbar)

        val pagerAdapter = SectionsPagerAdapter(supportFragmentManager, loggedInUserId)
        val pager = findViewById<View>(R.id.pager) as ViewPager
        pager.adapter = pagerAdapter

        val tabLayout = this.findViewById<TabLayout>(R.id.tabs)
        tabLayout.setupWithViewPager(pager)


    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.menu_main, menu)

        return super.onCreateOptionsMenu(menu)
    }

    override fun itemClicked(id: Int) {

        var fragmentContainer = findViewById<FrameLayout>(R.id.fragmentContainer)
        if (fragmentContainer != null) {
            val trackDetailsFragment = TrackDetailsFragment()
            trackDetailsFragment.setTrack(id)
            trackDetailsFragment.setLoggedInUserId(loggedInUserId)

            var transaction = supportFragmentManager.beginTransaction()
            transaction.replace(R.id.fragmentContainer, trackDetailsFragment)
            transaction.addToBackStack(null)
            transaction.setTransition(TRANSIT_FRAGMENT_FADE)
            transaction.commit()
        }
        else {
            val intent = Intent(this, TrackDetailsActivity::class.java)
            intent.putExtra(TrackDetailsActivity.TRACK_ID_KEY, id)
            intent.putExtra("loggedInUserId", loggedInUserId)
            startActivity(intent)
        }
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.itemId) {
            R.id.action_action -> {
                val intent = Intent(this, ActionActivity::class.java)
                startActivity(intent)
                return true
            }
            else -> {
                return super.onOptionsItemSelected(item)
            }
        }
    }

    private class SectionsPagerAdapter(fm: FragmentManager?, loggedInUserId: Int) : FragmentPagerAdapter(fm!!) {
        val loggedInUserId = loggedInUserId

        override fun getCount(): Int {
            return 3
        }

        override fun getItem(position: Int): Fragment {
            var trackListFragment = TrackListFragment()
            when (position) {
                0 -> {
                    trackListFragment.trackDifficultyName = "easy"
                }
                1 -> {
                    trackListFragment.trackDifficultyName = "medium"
                }
                2 -> {
                    trackListFragment.trackDifficultyName = "hard"
                }
            }
            trackListFragment.loggedInUserId = this.loggedInUserId
            return trackListFragment
        }

        override fun getPageTitle(position: Int): CharSequence? {
            when (position) {
                0 -> return "Easy Tracks"
                1 -> return "Medium Tracks"
                2 -> return "Hard Tracks"
            }
            return null
        }
    }
}