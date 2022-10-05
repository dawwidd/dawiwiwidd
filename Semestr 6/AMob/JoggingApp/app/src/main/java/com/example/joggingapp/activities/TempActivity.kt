package com.example.joggingapp.activities

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.fragment.app.FragmentTransaction
import com.example.joggingapp.R
import com.example.joggingapp.fragments.StopperFragment

class TempActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_temp)

        if (savedInstanceState == null) {
            val stopperFragment = StopperFragment()

            var transaction = supportFragmentManager.beginTransaction()
            transaction.add(R.id.stopperContainer, stopperFragment)
            transaction.addToBackStack(null)
            transaction.setTransition(FragmentTransaction.TRANSIT_FRAGMENT_FADE)
            transaction.commit()
        }


    }
}