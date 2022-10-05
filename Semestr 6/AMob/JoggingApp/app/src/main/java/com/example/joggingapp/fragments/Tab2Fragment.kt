package com.example.joggingapp.fragments

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import androidx.fragment.app.ListFragment
import com.example.joggingapp.R

class Tab2Fragment : ListFragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {

        var adapter = ArrayAdapter<String>(inflater.context, android.R.layout.simple_list_item_1, resources.getStringArray(R.array.category1))

        listAdapter = adapter

        return super.onCreateView(inflater, container, savedInstanceState)
    }
}