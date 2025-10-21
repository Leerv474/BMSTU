package com.example.lab7

import android.app.PendingIntent
import android.appwidget.AppWidgetManager
import android.appwidget.AppWidgetProvider
import android.content.ComponentName
import android.content.Context
import android.content.Intent
import android.graphics.Bitmap
import android.graphics.ImageDecoder
import android.net.Uri
import android.os.Build
import android.provider.MediaStore
import android.widget.RemoteViews
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlinx.coroutines.launch

class PhotoWidget : AppWidgetProvider() {

    companion object {
        const val ACTION_REFRESH_IMAGE = "com.example.lab7.ACTION_REFRESH_IMAGE"
    }

    override fun onUpdate(
        context: Context,
        appWidgetManager: AppWidgetManager,
        appWidgetIds: IntArray
    ) {
        for (appWidgetId in appWidgetIds) {
            updateAppWidget(context, appWidgetManager, appWidgetId)
            setClickListener(context, appWidgetManager, appWidgetId)
        }
    }

    override fun onReceive(context: Context, intent: Intent) {
        super.onReceive(context, intent)
        if (intent.action == ACTION_REFRESH_IMAGE) {
            val appWidgetManager = AppWidgetManager.getInstance(context)
            val appWidgetIds = appWidgetManager.getAppWidgetIds(
                ComponentName(context, PhotoWidget::class.java)
            )
            for (appWidgetId in appWidgetIds) {
                updateAppWidget(context, appWidgetManager, appWidgetId)
            }
        }
    }

    private fun setClickListener(
        context: Context,
        appWidgetManager: AppWidgetManager,
        appWidgetId: Int
    ) {
        val intent = Intent(context, PhotoWidget::class.java).apply {
            action = ACTION_REFRESH_IMAGE
        }
        val pendingIntent = PendingIntent.getBroadcast(
            context,
            0,
            intent,
            PendingIntent.FLAG_UPDATE_CURRENT or PendingIntent.FLAG_IMMUTABLE
        )
        val views = RemoteViews(context.packageName, R.layout.photo_widget)
        views.setOnClickPendingIntent(R.id.imageView, pendingIntent)
        appWidgetManager.updateAppWidget(appWidgetId, views)
    }
}

// ------------------- Helper function -------------------

private var widgetJob: Job? = null

internal fun updateAppWidget(
    context: Context,
    appWidgetManager: AppWidgetManager,
    appWidgetId: Int
) {
    widgetJob?.cancel()
    val views = RemoteViews(context.packageName, R.layout.photo_widget)
    views.setImageViewResource(R.id.imageView, R.drawable.app_widget_background)
    appWidgetManager.updateAppWidget(appWidgetId, views)

    widgetJob = CoroutineScope(Dispatchers.IO).launch {
        val imageUri: Uri? = ImageHelper.getRandomImage(context)
        val bitmap: Bitmap? = imageUri?.let { loadBitmapFromUri(context, it, 200, 200) }

        bitmap?.let {
            CoroutineScope(Dispatchers.Main).launch {
                views.setImageViewBitmap(R.id.imageView, it)
                appWidgetManager.updateAppWidget(appWidgetId, views)
            }
        }
    }
}

private fun loadBitmapFromUri(context: Context, uri: Uri, maxWidth: Int, maxHeight: Int): Bitmap? {
    return try {
        val original = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            val source = ImageDecoder.createSource(context.contentResolver, uri)
            ImageDecoder.decodeBitmap(source)
        } else {
            MediaStore.Images.Media.getBitmap(context.contentResolver, uri)
        }

        // Calculate scale factor
        val ratio = minOf(
            maxWidth.toFloat() / original.width,
            maxHeight.toFloat() / original.height
        )
        val width = (original.width * ratio).toInt()
        val height = (original.height * ratio).toInt()

        Bitmap.createScaledBitmap(original, width, height, true).also {
            if (it != original) original.recycle()
        }
    } catch (e: Exception) {
        e.printStackTrace()
        null
    }
}
