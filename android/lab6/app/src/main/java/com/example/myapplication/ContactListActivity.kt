package com.example.myapplication

import android.database.Cursor
import androidx.appcompat.app.AppCompatActivity

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.BaseAdapter
import android.widget.GridView
import android.widget.TextView
import android.widget.Toast

class ContactListActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_contacts)

        var contactsList = findViewById<GridView>(R.id.contactsList)

        val searchQuery = intent.getStringExtra("SEARCH_QUERY") ?: ""

        val selection: String?
        val selectionArgs: Array<String>?

        if (searchQuery.isEmpty()) {
            // No filtering
            selection = null
            selectionArgs = null
        } else {
            // Filter by surname
            selection = "surname LIKE ?"
            selectionArgs = arrayOf("%$searchQuery%")
        }
        val cursor = contentResolver.query(
            ContactsProvider.CONTENT_URI,
            arrayOf("surname", "name", "phone_number"),
            selection,
            selectionArgs,
            "name ASC"
        )

        if (cursor == null || cursor.count == 0) {
            Toast.makeText(this, "Cursor is null", Toast.LENGTH_SHORT).show()
        }

        val results = mutableListOf<String>()
        cursor?.use {
            while (it.moveToNext()) {
                val surname = it.getString(it.getColumnIndexOrThrow("surname"))
                val name = it.getString(it.getColumnIndexOrThrow("name"))
                val phone = it.getString(it.getColumnIndexOrThrow("phone_number"))
                results.add("$surname $name: $phone")
            }
        }

        results.ifEmpty {
            Toast.makeText(this, "Nothing found", Toast.LENGTH_SHORT).show()
        }

        val adapter = object : BaseAdapter() {
            override fun getCount(): Int {
                return results.size
            }

            override fun getItem(position: Int): Any? {
                return results[position]
            }

            override fun getItemId(position: Int): Long {
                return position.toLong()
            }

            override fun getView(
                position: Int,
                convertView: View?,
                parent: ViewGroup?
            ): View? {
                val view = convertView ?: LayoutInflater.from(this@ContactListActivity)
                    .inflate(R.layout.contacts_item, parent, false)
                val textView = view.findViewById<TextView>(R.id.grid_item_text)
                textView.text = results[position]
                return view
            }

        }
        contactsList.adapter = adapter
    }
}