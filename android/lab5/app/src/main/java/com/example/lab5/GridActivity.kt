package com.example.lab5

import android.graphics.Color
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.BaseAdapter
import android.widget.GridView
import android.widget.TextView
import androidx.activity.ComponentActivity
import androidx.core.graphics.toColorInt

class GridActivity: ComponentActivity(){
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.grid_activity)

        val numberOfColumns = intent.getIntExtra("NUM_COLUMNS", 1)
        val horizontalSpacing = intent.getIntExtra("HORIZONTAL_SPACING", 0)
        val backgroundColor = intent.getStringExtra("COLOR") ?: "#FFFFFF"
        print(backgroundColor)

        val gridView = findViewById<GridView>(R.id.gridView)
        val items = listOf("A", "B", "C", "D", "E", "F", "G", "H", "I")

        val adapter = object:  BaseAdapter() {
            override fun getCount() = items.size

            override fun getItem(position: Int) = items[position]

            override fun getItemId(position: Int) = position.toLong()

            override fun getView(
                position: Int,
                convertView: View?,
                parent: ViewGroup?
            ): View? {
                val view = convertView?: LayoutInflater.from(this@GridActivity).inflate(R.layout.grid_item, parent, false)
                val textView = view.findViewById<TextView>(R.id.grid_item_text)
                textView.text = items[position]
                textView.setBackgroundColor(backgroundColor.toColorInt())

                return view
            }
        }

        gridView.horizontalSpacing = horizontalSpacing
        gridView.numColumns = numberOfColumns
        gridView.adapter = adapter
    }
}