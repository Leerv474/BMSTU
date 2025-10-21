package com.example.lab7;

import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.provider.MediaStore;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class ImageHelper {
    public static Uri getRandomImage(Context context) {
        List<Uri> images = new ArrayList<>();
        Uri collection = MediaStore.Images.Media.EXTERNAL_CONTENT_URI;

        String[] projection = { MediaStore.Images.Media._ID };

        try (Cursor cursor = context.getContentResolver().query(
                collection,
                projection,
                null,
                null,
                null
        )) {
            if (cursor != null) {
                int idColumn = cursor.getColumnIndexOrThrow(MediaStore.Images.Media._ID);

                while (cursor.moveToNext()) {
                    long id = cursor.getLong(idColumn);
                    Uri contentUri = Uri.withAppendedPath(collection, String.valueOf(id));
                    images.add(contentUri);
                }
            }
        }

        if (!images.isEmpty()) {
            Random random = new Random();
            return images.get(random.nextInt(images.size()));
        } else {
            return null;
        }
    }
}
