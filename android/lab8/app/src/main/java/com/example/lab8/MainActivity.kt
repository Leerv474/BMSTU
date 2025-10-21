package com.example.lab8

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import androidx.activity.ComponentActivity
import androidx.activity.enableEdgeToEdge


class MainActivity : ComponentActivity() {
    private lateinit var maxRateInput: EditText
    private lateinit var startButton: Button
    private lateinit var stopButton: Button
    private var isEnabled = false

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.main)

        maxRateInput = findViewById(R.id.valueInput)
        startButton = findViewById(R.id.startButton)
        stopButton = findViewById(R.id.stopButton)

        startButton.setOnClickListener { v -> startService()}
        stopButton.setOnClickListener { v ->  stopService() }
    }


    private fun startService() {
        if (isEnabled) {
            return
        }
        isEnabled = true
        val rate = maxRateInput.getText().toString().toFloat()
        val intent = Intent(this, BatteryMonitorService::class.java)
        intent.putExtra("maxRate", rate)
        startService(intent)
    }

    private fun stopService() {
        if (!isEnabled) {
            return
        }
        isEnabled = false
        val intent = Intent(this, BatteryMonitorService::class.java)
        stopService(intent)
    }
}