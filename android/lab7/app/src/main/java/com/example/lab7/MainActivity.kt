package com.example.lab7

import android.os.Bundle
import android.widget.ImageView
import androidx.activity.ComponentActivity
import androidx.activity.enableEdgeToEdge
import com.bumptech.glide.Glide


class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.photo_widget)


        val imageView = findViewById<ImageView>(R.id.imageView)
        val randomImage = ImageHelper.getRandomImage(this)
        if (randomImage != null) {
            Glide.with(this).load(randomImage).into(imageView)
        }
    }
}