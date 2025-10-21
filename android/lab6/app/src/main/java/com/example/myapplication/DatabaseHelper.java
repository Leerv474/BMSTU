package com.example.myapplication;

import android.content.ContentValues;
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import androidx.annotation.Nullable;

public class DatabaseHelper extends SQLiteOpenHelper {
    private static final String DATABASE_NAME = "phonebook_db";
    private static final int DATABASE_VERSION = 2;

    private static final String TABLE_NAME = "contacts";
    private static final String COLUMN_ID = "id";
    private static final String COLUMN_SURNAME = "surname";
    private static final String COLUMN_NAME = "name";
    private static final String COLUMN_PHONE_NUMBER = "phone_number";
    public DatabaseHelper(@Nullable Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        String createTable = String.format(
                "CREATE TABLE %s ( %s INTEGER PRIMARY KEY AUTOINCREMENT, %s TEXT, %s TEXT, %s TEXT )",
                TABLE_NAME, COLUMN_ID, COLUMN_SURNAME, COLUMN_NAME, COLUMN_PHONE_NUMBER
        );
        db.execSQL(createTable);
        insertInitialData(db);
    }


    private void insertInitialData(SQLiteDatabase db) {
        insertContact(db, "Smith", "Alice", "123456789");
        insertContact(db, "Johnson", "Bob", "987654321");
        insertContact(db, "Brown", "Charlie", "555666777");
        insertContact(db, "Miller", "David", "111222333");
        insertContact(db, "Davis", "Emma", "222333444");
        insertContact(db, "Garcia", "Frank", "333444555");
        insertContact(db, "Martinez", "Grace", "444555666");
        insertContact(db, "Wilson", "Hannah", "555666777");
        insertContact(db, "Anderson", "Ian", "666777888");
        insertContact(db, "Thomas", "Julia", "777888999");
        insertContact(db, "Taylor", "Kevin", "888999000");
        insertContact(db, "Moore", "Laura", "999000111");
        insertContact(db, "Jackson", "Michael", "101112131");
        insertContact(db, "White", "Nina", "121314151");
        insertContact(db, "Harris", "Oliver", "131415161");
        insertContact(db, "Martin", "Paula", "141516171");
        insertContact(db, "Thompson", "Quinn", "151617181");
        insertContact(db, "Lee", "Rachel", "161718192");
        insertContact(db, "Perez", "Steven", "171819202");
        insertContact(db, "Young", "Tina", "181920212");
        insertContact(db, "Hall", "Uma", "192021222");
        insertContact(db, "Allen", "Victor", "202122232");
        insertContact(db, "Sanchez", "Wendy", "212223242");
        insertContact(db, "Wright", "Xavier", "222324252");
    }

    private void insertContact(SQLiteDatabase db, String surname, String name, String phone) {
        ContentValues values = new ContentValues();
        values.put(COLUMN_SURNAME, surname);
        values.put(COLUMN_NAME, name);
        values.put(COLUMN_PHONE_NUMBER, phone);
        db.insert(TABLE_NAME, null, values);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS contacts");
        onCreate(db);
    }
}
