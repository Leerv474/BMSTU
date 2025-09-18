package com.example.lab3

import android.graphics.Color
import android.os.Bundle
import android.view.Gravity
import android.view.View
import android.widget.Button
import android.widget.ImageButton
import android.widget.RadioGroup
import android.widget.TextView
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.core.graphics.toColorInt
import com.example.lab3.ui.theme.Lab3Theme

class MainActivity : ComponentActivity() {
    private lateinit var textView: TextView
    private lateinit var textSizesGroup: RadioGroup
    private lateinit var colorButtons: Map<String, ImageButton?>
    private lateinit var alignLeftButton: Button
    private lateinit var alignCenterButton: Button
    private lateinit var alignRightButton: Button
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)
        setupElements()

        textSizesGroup.setOnCheckedChangeListener { _, checkedId ->
            when (checkedId) {
                R.id.radioButton12 -> textView.textSize = 12f
                R.id.radioButton14 -> textView.textSize = 14f
                R.id.radioButton16 -> textView.textSize = 16f
                R.id.radioButton18 -> textView.textSize = 18f
                R.id.radioButton20 -> textView.textSize = 20f
                R.id.radioButton24 -> textView.textSize = 24f
            }
        }
        colorButtons.forEach { (hex, button) ->
            button?.setOnClickListener {
                if (hex != "randomize") {
                    textView.setTextColor(hex.toColorInt())
                } else {
                    val colorKeys = colorButtons.keys.filter { it.startsWith("#") }
                    val randomHex = colorKeys.random()
                    textView.setTextColor(randomHex.toColorInt())
                }
            }
        }

        alignLeftButton.setOnClickListener {
            textView.gravity = Gravity.START or Gravity.CENTER_VERTICAL
        }

        alignCenterButton.setOnClickListener {
            textView.gravity = Gravity.CENTER
        }

        alignRightButton.setOnClickListener {
            textView.gravity = Gravity.END or Gravity.CENTER_VERTICAL
        }
    }

    fun setupElements() {
        this.colorButtons = mapOf(
            "#000000" to findViewById(R.id.blackButton),       // Black
            "#FFFFFF" to findViewById(R.id.whiteButton),       // White
            "#B71C1C" to findViewById(R.id.redButton),         // Holo red dark
            "#0D47A1" to findViewById(R.id.blueButton),        // Holo blue dark
            "#1B5E20" to findViewById(R.id.greenButton),       // Holo green dark
            "#FBC02D" to findViewById(R.id.yellowButton),      // Holo orange light (yellowish)
            "#BB86FC" to findViewById(R.id.purpleButton),      // Purple (Material purple_200)
            "#6E7487" to findViewById(R.id.grayButton),        // Custom gray
            "#E65100" to findViewById(R.id.orangeButton),      // Holo orange dark
            "#03DAC5" to findViewById(R.id.tealButton),        // Teal (Material teal_200)
            "#FAD3F7" to findViewById(R.id.pinkButton),        // Custom pink
            "#FF00FF" to findViewById(R.id.magentaButton),     // Magenta
            "#795548" to findViewById(R.id.brownButton),       // Brown
            "#FFFFE0" to findViewById(R.id.lightYellow),       // Light yellow
            "#90EE90" to findViewById(R.id.lightGreen),        // Holo green light (approx)
            "randomize" to findViewById(R.id.randomizeColorButton) // Special case
        )
        this.textSizesGroup = findViewById(R.id.textSizesGroup)
        this.textView = findViewById(R.id.textView)
        this.alignLeftButton = findViewById(R.id.alignLeft)
        this.alignCenterButton = findViewById(R.id.alignCenter)
        this.alignRightButton = findViewById(R.id.alignRight)
    }
}
