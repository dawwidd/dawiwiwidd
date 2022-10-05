package com.example.guessthenumber

import android.content.ContentValues
import android.content.Context
import android.database.Cursor
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper
import java.security.AccessControlContext

class DBHelper(context: Context): SQLiteOpenHelper(context, DBNAME, null, DBVERSION) {

    companion object {
        private val DBVERSION = 1
        private val DBNAME = "guessTheNumber.db"

        private val TABLE_NAME = "Users"
        private val COL_ID = "id"
        private val COL_USERNAME = "username"
        private val COL_PASSWORD = "password"
        private val COL_SCORE = "score"
    }

    override fun onCreate(db: SQLiteDatabase) {
        var query = ("CREATE TABLE IF NOT EXISTS $TABLE_NAME ($COL_ID INTEGER PRIMARY KEY AUTOINCREMENT," +
                "$COL_USERNAME TEXT," +
                "$COL_PASSWORD TEXT," +
                "$COL_SCORE INTEGER)")

        db!!.execSQL(query)
    }


    override fun onUpgrade(db: SQLiteDatabase, p1: Int, p2: Int) {
        db!!.execSQL("DROP TABLE IF EXISTS $TABLE_NAME")
        onCreate(db!!)
    }

    fun createUser(username: String, password: String) {
        val db = this.writableDatabase
        val values = ContentValues()

        values.put(COL_USERNAME, username)
        values.put(COL_PASSWORD, password)
        values.put(COL_SCORE, 0)

        db.insert(TABLE_NAME, null, values)
        db.close()
    }

    fun checkIfUserExists(username: String): Boolean {
        val db = this.readableDatabase

        var cursor = db.rawQuery("SELECT * FROM $TABLE_NAME WHERE $COL_USERNAME='$username'", null)

        return cursor.count > 0
    }

    fun checkPassword(username: String, password: String): Boolean {
        val db = this.readableDatabase

        var cursor = db.rawQuery("SELECT * FROM $TABLE_NAME WHERE $COL_USERNAME='$username' AND $COL_PASSWORD='$password'", null)

        return cursor.count > 0
    }

    fun getScore(username: String): Int {
        val db = this.readableDatabase
        var cursor = db.rawQuery("SELECT $COL_SCORE FROM $TABLE_NAME WHERE $COL_USERNAME='$username'", null)
        cursor!!.moveToFirst()

        var score = cursor.getInt(cursor.getColumnIndexOrThrow(COL_SCORE))

        db.close()
        return score
    }

    fun updateScore(username: String, score: Int) {
        val db = this.writableDatabase
        val query = ("UPDATE $TABLE_NAME SET $COL_SCORE='$score' WHERE $COL_USERNAME='$username'")

        db.execSQL(query)
        db.close()
    }

    fun getScoreboard(): ArrayList<User> {
        val db = this.readableDatabase
        var cursor = db.rawQuery("SELECT $COL_USERNAME, $COL_SCORE FROM $TABLE_NAME ORDER BY $COL_SCORE DESC", null)

        var userList = ArrayList<User>()

        if(cursor.moveToFirst()) {
            do {
                val user = User()
                user.username = cursor.getString(cursor.getColumnIndexOrThrow(COL_USERNAME))
                user.score = cursor.getInt(cursor.getColumnIndexOrThrow(COL_SCORE))
                userList.add(user)
            } while(cursor.moveToNext())
        }
        db.close()
        return userList
    }

}