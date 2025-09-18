package com.example.lab2

import android.graphics.Color
import android.os.Bundle
import android.view.View
import android.widget.AdapterView
import android.widget.ArrayAdapter
import android.widget.RadioGroup
import android.widget.Spinner
import android.widget.TextView
import androidx.activity.ComponentActivity
import androidx.activity.enableEdgeToEdge

class MainActivity : ComponentActivity() {
    private lateinit var textView1: TextView
    private lateinit var textView2: TextView
    private lateinit var textView3: TextView
    private lateinit var radioGroup: RadioGroup

    private var selectedTextView: TextView? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)

        textView1 = findViewById(R.id.textView1)
        textView2 = findViewById(R.id.textView2)
        textView3 = findViewById(R.id.textView3)
        radioGroup = findViewById(R.id.radioGroup)

        radioGroup.setOnCheckedChangeListener { _, checkedId ->
            selectedTextView = when (checkedId) {
                R.id.radioButton1 -> textView1
                R.id.radioButton2 -> textView2
                R.id.radioButton3 -> textView3
                else -> null
            }
        }

        val fontSizes = intArrayOf(10, 12, 14, 16, 18, 20, 22, 24)
        val fontSizeStrings = fontSizes.map { it.toString() }

        val fontSizeSpinner = findViewById<Spinner>(R.id.font_size_spinner)
        val adapter = ArrayAdapter(
            this,
            android.R.layout.simple_spinner_item,
            fontSizeStrings
        )
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        fontSizeSpinner.adapter = adapter

        fontSizeSpinner.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            override fun onItemSelected(
                parent: AdapterView<*>?,
                view: View?,
                position: Int,
                id: Long
            ) {
                val size = fontSizes[position]
                selectedTextView?.textSize = size.toFloat()
            }

            override fun onNothingSelected(parent: AdapterView<*>) {}
        }


        val colorValues =
            listOf(Color.BLACK, Color.WHITE, Color.RED, Color.GREEN, Color.BLUE, Color.YELLOW)
        val colorNames = listOf(
            "Black",
            "White",
            "Red",
            "Green",
            "Blue",
            "Yellow"
        )
        val backgroundColorSpinner = findViewById<Spinner>(R.id.background_color_spinner)
        val colorArrayAdapter = ArrayAdapter(
            this,
            android.R.layout.simple_spinner_item,
            colorNames
        )
        colorArrayAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        backgroundColorSpinner.adapter = colorArrayAdapter

        backgroundColorSpinner.onItemSelectedListener =
            object : AdapterView.OnItemSelectedListener {
                override fun onItemSelected(
                    parent: AdapterView<*>?,
                    view: View?,
                    position: Int,
                    id: Long
                ) {
                    selectedTextView?.setBackgroundColor(colorValues[position])
                }

                override fun onNothingSelected(parent: AdapterView<*>) {}
            }

        val fontColorSpinner = findViewById<Spinner>(R.id.font_color_spinner)
        fontColorSpinner.adapter = colorArrayAdapter
        fontColorSpinner.onItemSelectedListener =
            object : AdapterView.OnItemSelectedListener {
                override fun onItemSelected(
                    parent: AdapterView<*>?,
                    view: View?,
                    position: Int,
                    id: Long
                ) {
                    selectedTextView?.setTextColor(colorValues[position])
                }

                override fun onNothingSelected(parent: AdapterView<*>?) {}
            }
    }
}
