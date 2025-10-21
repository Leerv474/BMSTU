package com.example.lab4

import android.os.Bundle
import android.view.View
import android.widget.AdapterView
import android.widget.ArrayAdapter
import android.widget.Spinner
import android.widget.TextView
import androidx.activity.ComponentActivity
import androidx.activity.enableEdgeToEdge
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.example.lab4.ui.theme.Lab4Theme


class MainActivity : ComponentActivity() {
    private lateinit var adminName: TextView
    private lateinit var squareArea: TextView
    private lateinit var numberOfWindows: TextView
    private lateinit var isSirenSetup: TextView
    private lateinit var numberOfTables: TextView
    private lateinit var numberOfPcs: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.layout_main)


        adminName = findViewById<TextView>(R.id.admin_name)
        squareArea = findViewById<TextView>(R.id.square_area)
        numberOfWindows = findViewById<TextView>(R.id.number_of_windows)
        isSirenSetup = findViewById<TextView>(R.id.is_siren_setup)
        numberOfTables = findViewById<TextView>(R.id.number_of_tables)
        numberOfPcs = findViewById<TextView>(R.id.number_of_pcs)

        val dbHelper = DatabaseHelper(this)
        val classroomNumbers = dbHelper.getListOfClassrooms()

        val classroomSpinner = findViewById<Spinner>(R.id.classroomSpinner)
        val adapter = ArrayAdapter(
            this,
            android.R.layout.simple_spinner_item,
            classroomNumbers
        )
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        classroomSpinner.adapter = adapter

        classroomSpinner.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            override fun onItemSelected(
                parent: AdapterView<*>?,
                view: View?,
                position: Int,
                id: Long
            ) {
                val classroomData = dbHelper.getClassroomData(classroomNumbers[position].toInt())
                adminName.text = classroomData["admin_name"]
                squareArea.text = classroomData["square_area"]
                numberOfWindows.text = classroomData["number_of_windows"] + " шт."
                if (classroomData["is_siren_setup"]?.toInt() == 1) {
                    isSirenSetup.text = "присутствует"
                } else {
                    isSirenSetup.text = "отсутствует"
                }
                numberOfTables.text = classroomData["number_of_tables"] + " шт."
                numberOfPcs.text = classroomData["number_of_pcs"] + " шт."
            }

            override fun onNothingSelected(parent: AdapterView<*>?) {}
        }
    }
}