package com.example.lab4;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import androidx.annotation.Nullable;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class DatabaseHelper extends SQLiteOpenHelper {
    private static final String DATABASE_NAME = "classrooms.db";
    private static final int DATABASE_VERSION = 1;

    private static final String TABLE_CLASSROOMS = "classrooms";
    private static final String COLUMN_ID = "id";
    private static final String COLUMN_ADMIN_NAME = "admin_name";
    private static final String SQUARE_AREA = "square_area";
    private static final String NUMBER_OF_WINDOWS = "number_of_windows";
    private static final String IS_SIREN_SETUP = "is_siren_setup";
    private static final String NUMBER_OF_TABLES = "number_of_tables";
    private static final String NUMBER_OF_PCS = "number_of_pcs";

    public DatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        String createTable = String.format("CREATE TABLE %s ( %s INTEGER PRIMARY KEY AUTOINCREMENT, %s text, %s text, %s integer, %s integer, %s integer, %s integer)",
                TABLE_CLASSROOMS, COLUMN_ID, COLUMN_ADMIN_NAME, SQUARE_AREA, NUMBER_OF_WINDOWS, IS_SIREN_SETUP, NUMBER_OF_TABLES, NUMBER_OF_PCS);
        db.execSQL(createTable);

        for (int i = 1; i <= 20; i++) {
            ContentValues values = new ContentValues();
            values.put(COLUMN_ADMIN_NAME, "Admin " + i);
            values.put(SQUARE_AREA, (20 + i * 5) + " sqm");
            values.put(NUMBER_OF_WINDOWS, i % 5 + 1);
            values.put(IS_SIREN_SETUP, i % 2);
            values.put(NUMBER_OF_TABLES, 10 + i);
            values.put(NUMBER_OF_PCS, 5 + (i % 10));
            db.insert(TABLE_CLASSROOMS, null, values);
        }
    }
    public void insertClassroom(String adminName, String squareArea,
                                int numberOfWindows, int isSirenSetup,
                                int numberOfTables, int numberOfPcs) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put(COLUMN_ADMIN_NAME, adminName);
        values.put(SQUARE_AREA, squareArea);
        values.put(NUMBER_OF_WINDOWS, numberOfWindows);
        values.put(IS_SIREN_SETUP, isSirenSetup); // 0 = false, 1 = true
        values.put(NUMBER_OF_TABLES, numberOfTables);
        values.put(NUMBER_OF_PCS, numberOfPcs);

        db.insert(TABLE_CLASSROOMS, null, values);
        db.close();
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_CLASSROOMS);
    }

    public List<String> getListOfClassrooms() {
        List<String> listOfClassrooms = new ArrayList<>();
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.rawQuery("select id from " + TABLE_CLASSROOMS, null);
        if (cursor.moveToFirst()) {
            do {
                String classroomId = cursor.getString(cursor.getColumnIndexOrThrow(COLUMN_ID));
                listOfClassrooms.add(classroomId);
            } while (cursor.moveToNext());
        }
        cursor.close();
        db.close();
        return listOfClassrooms;
    }

    public Map<String, String> getClassroomData(int classroomId) {
        Map<String, String> classroomData = new HashMap<>();
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.rawQuery("select * from " + TABLE_CLASSROOMS + " where id = " + classroomId + ";", null);

        if (cursor.moveToFirst()) {
            classroomData.put(COLUMN_ADMIN_NAME, cursor.getString(cursor.getColumnIndexOrThrow(COLUMN_ADMIN_NAME)));
            classroomData.put(SQUARE_AREA, cursor.getString(cursor.getColumnIndexOrThrow(SQUARE_AREA)));
            classroomData.put(NUMBER_OF_WINDOWS, cursor.getString(cursor.getColumnIndexOrThrow(NUMBER_OF_WINDOWS)));
            classroomData.put(IS_SIREN_SETUP, cursor.getString(cursor.getColumnIndexOrThrow(IS_SIREN_SETUP)));
            classroomData.put(NUMBER_OF_TABLES, cursor.getString(cursor.getColumnIndexOrThrow(NUMBER_OF_TABLES)));
            classroomData.put(NUMBER_OF_PCS, cursor.getString(cursor.getColumnIndexOrThrow(NUMBER_OF_PCS)));
        }

        cursor.close();
        db.close();
        return classroomData;
    }


}
