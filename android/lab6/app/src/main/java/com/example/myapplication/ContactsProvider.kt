package com.example.myapplication

import android.content.ContentProvider
import android.content.ContentValues
import android.database.Cursor
import android.net.Uri
import android.util.Log
import android.widget.Toast

class ContactsProvider: ContentProvider() {
    companion object {
        const val AUTHORITY = "com.example.lab6.contactsprovider"
        val CONTENT_URI: Uri = Uri.parse("content://$AUTHORITY/contacts")
    }
    private lateinit var dbHelper: DatabaseHelper

    override fun onCreate(): Boolean {
        context?.let { dbHelper = DatabaseHelper(it) } ?: return false
        dbHelper.readableDatabase
        return true
    }

    override fun query(
        uri: Uri,
        projection: Array<out String?>?,
        selection: String?,
        selectionArgs: Array<out String?>?,
        sortOrder: String?
    ): Cursor? {
        return try {
            val db = dbHelper.readableDatabase
            val cursor = db.query("contacts", projection, selection, selectionArgs, null, null, sortOrder)
            cursor
        } catch (e: Exception) {
            Log.e("ContactsProvider", "Query failed", e)
            null
        }
    }

    override fun insert(
        uri: Uri,
        values: ContentValues?
    ): Uri? {
        val db = dbHelper.writableDatabase
        val id = db.insert("contacts", null, values)
        return Uri.withAppendedPath(CONTENT_URI, id.toString())
    }

    override fun delete(
        uri: Uri,
        selection: String?,
        selectionArgs: Array<out String?>?
    ): Int {
        val db = dbHelper.writableDatabase
        return db.delete("contacts", selection, selectionArgs)
    }

    override fun getType(uri: Uri): String? {
        return "vnd.android.cursor.dir/vnd.$AUTHORITY.contacts"
    }

    override fun update(
        uri: Uri,
        values: ContentValues?,
        selection: String?,
        selectionArgs: Array<out String?>?
    ): Int {
        val db = dbHelper.writableDatabase
        return db.update("contacts", values, selection, selectionArgs)
    }

}