package com.example.bialaroza.DB

import android.content.ContentValues
import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper
import com.example.bialaroza.Modal.Message

class DBHelper(context: Context):SQLiteOpenHelper(context,DATABASE_NAME,
    null, DATABASE_VER) {
    companion object {
        private val DATABASE_VER = 2
        private val DATABASE_NAME = "EDMTDB.db"
        //Table
        private val TABLE_NAME = "Message"
        private val COL_ID = "Id"
        private val COL_MESSAGE = "Info"
        private val COL_TYPE = "Type"
        private val COL_KEY = "Key"
    }

    override fun onCreate(db: SQLiteDatabase?) {
        val CREATE_TABLE_QUERY = ("CREATE TABLE $TABLE_NAME ($COL_ID INTEGER PRIMARY KEY AUTOINCREMENT, $COL_MESSAGE TEXT, $COL_TYPE TEXT, $COL_KEY TEXT)")
        db!!.execSQL(CREATE_TABLE_QUERY)
    }

    override fun onUpgrade(db: SQLiteDatabase?, oldVersion: Int, newVersion: Int) {
        db!!.execSQL("DROP TABLE IF EXISTS $TABLE_NAME")
        onCreate(db!!)
    }

    //CRUD
    val allMessage:List<Message>
        get(){
            val listMessage = ArrayList<Message>()
            val selectQuery = "SELECT * FROM $TABLE_NAME"
            val db = this.writableDatabase
            val cursor =  db.rawQuery(selectQuery, null)
            if(cursor.moveToFirst()){
                do {
                    val message = Message()
                    message.id = cursor.getInt(cursor.getColumnIndex(COL_ID))
                    message.info = cursor.getString(cursor.getColumnIndex(COL_MESSAGE))
                    message.type = cursor.getString(cursor.getColumnIndex(COL_TYPE))
                    message.key = cursor.getString(cursor.getColumnIndex(COL_KEY))

                    listMessage.add(message)
                } while (cursor.moveToNext())
            }
            db.close()
            return listMessage
        }

    fun addMessage(message:Message){
        val db= this.writableDatabase
        val values = ContentValues()
        values.put(COL_MESSAGE, message.info)
        values.put(COL_TYPE, message.type)
        values.put(COL_KEY, message.key)

        db.insert(TABLE_NAME, null, values)
        db.close()
    }

    fun testOne(key:String): Boolean {
        val selectQuery = "SELECT * FROM $TABLE_NAME WHERE $COL_KEY = '$key'"
        val db = this.writableDatabase
        val cursor = db.rawQuery(selectQuery, null)
        if (cursor.moveToFirst()){
            if(key == cursor.getString(cursor.getColumnIndex(COL_KEY))) {
                return false
            }
        }
        return true
    }

}