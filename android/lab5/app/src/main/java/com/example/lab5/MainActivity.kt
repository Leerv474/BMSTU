package com.example.lab5

import android.content.Intent
import android.graphics.Color
import android.os.Bundle
import android.view.View
import android.widget.AdapterView
import android.widget.ArrayAdapter
import android.widget.Button
import android.widget.ImageButton
import android.widget.Spinner
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.enableEdgeToEdge

class MainActivity : ComponentActivity() {
    private lateinit var numberOfColumnsSpinner: Spinner
    private lateinit var horizontalSpacingSpinner: Spinner
    private lateinit var colorButtons: Map<String, ImageButton?>
    private lateinit var applyButton: Button


    private var cellColor: String = "#000000"
    private var numberOfColumns = 1
    private var horizontalSpacing = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.main_layout)
        setupElements()

        val numberOfColumnsArray = listOf(1, 2, 3, 4, 5, 6, 7, 8, 9 ,10)
        val horizontalSpacingArray = listOf(0, 2, 4, 8, 16, 32, 64, 300)

        val numberOfColumnsAdapter = ArrayAdapter(
            this,
            android.R.layout.simple_spinner_item,
            numberOfColumnsArray
        )
        numberOfColumnsAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        numberOfColumnsSpinner.adapter = numberOfColumnsAdapter

        numberOfColumnsSpinner.onItemSelectedListener = object: AdapterView.OnItemSelectedListener {
            override fun onItemSelected(
                parent: AdapterView<*>?,
                view: View?,
                position: Int,
                id: Long
            ) {
                numberOfColumns = numberOfColumnsArray[position]
            }

            override fun onNothingSelected(parent: AdapterView<*>?) {}
        }

        val horizontalSpacingAdapter = ArrayAdapter(
            this,
            android.R.layout.simple_spinner_item,
            horizontalSpacingArray
        )
        horizontalSpacingAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        horizontalSpacingSpinner.adapter = horizontalSpacingAdapter

        horizontalSpacingSpinner.onItemSelectedListener = object: AdapterView.OnItemSelectedListener {
            override fun onItemSelected(
                parent: AdapterView<*>?,
                view: View?,
                position: Int,
                id: Long
            ) {
                horizontalSpacing = horizontalSpacingArray[position]
            }

            override fun onNothingSelected(parent: AdapterView<*>?) {}
        }

        colorButtons.forEach { (hex, button) ->
            button?.setOnClickListener {
                this.cellColor = hex
                Toast.makeText(this, "Button clicked!", Toast.LENGTH_SHORT).show()
            }
        }

        applyButton.setOnClickListener {
            val intent = Intent(this, GridActivity::class.java)
            intent.putExtra("NUM_COLUMNS", numberOfColumns)
            intent.putExtra("HORIZONTAL_SPACING", horizontalSpacing)
            intent.putExtra("COLOR", cellColor)
            startActivity(intent)
        }
    }

    fun setupElements() {
        this.colorButtons = mapOf(
            "#000000" to findViewById(R.id.blackButton),       // Black
            "#FFFFFF" to findViewById(R.id.whiteButton),       // White
            "#B71C1C" to findViewById(R.id.redButton),         // Holo red dark
            "#1B5E20" to findViewById(R.id.greenButton),       // Holo green dark
            "#BB86FC" to findViewById(R.id.purpleButton),      // Purple (Material purple_200)
            "#E65100" to findViewById(R.id.orangeButton),      // Holo orange dark
        )
        this.numberOfColumnsSpinner = findViewById(R.id.numberOfColumnSpinner)
        this.horizontalSpacingSpinner = findViewById(R.id.horizontalSpacingSpinner)
        this.applyButton = findViewById(R.id.applyButton)
    }
}