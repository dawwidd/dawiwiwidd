package com.example.guessthenumber

import android.app.AlertDialog
import android.content.DialogInterface
import android.content.Intent
import android.os.Bundle
import android.view.Gravity
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import kotlin.random.Random


class MainActivity : AppCompatActivity() {

//    var score = 0;
//
//    fun setRecord(){
//        val sharedScore = this.getSharedPreferences("com.example.myapplication.shared",0)
//        val edit = sharedScore.edit()
//        edit.putInt("score", score)
//        edit.apply()
//    }
//
//    fun getRecord(){
//        val sharedScore = this.getSharedPreferences("com.example.myapplication.shared",0)
//        score = sharedScore.getInt("score", 0)
//    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val guessButton = findViewById<Button>(R.id.guessButton)
        val newGameButton = findViewById<Button>(R.id.newGameButton)
        val scoreboardButton = findViewById<Button>(R.id.scoreboardButtonM)
        val db = DBHelper(applicationContext)

        val numberOfGuessesText = findViewById<TextView>(R.id.numberOfGuessesText)
        updateNumberOfGuessesText(numberOfGuessesText, 0)
        val scoreText = findViewById<TextView>(R.id.scoreText)
        updateScoreText(scoreText, 0)
        val textInput = findViewById<EditText>(R.id.simpleEditText)
        var numbertoGuess = Random.nextInt(0, 20)
        var guessedNumber = ""
        var numberOfGuesses = 0
        val intent = intent
        var username = intent.getStringExtra("username")
        var score = db.getScore(username!!)


        updateScoreText(scoreText, score);

        guessButton.setOnClickListener() {
            guessedNumber = textInput.getText().toString();
            try {
                if (guessedNumber.toInt() <= 20 && guessedNumber.toInt() >= 0) {
                    if(numberOfGuesses < 10) {
                        if(guessedNumber.toInt() > numbertoGuess) {
                            val toast = Toast.makeText(applicationContext, "The number I chose is smaller", Toast.LENGTH_LONG);
                            toast.setGravity(Gravity.CENTER_VERTICAL, 0, 200);
                            toast.show();

                            updateNumberOfGuessesText(numberOfGuessesText, ++numberOfGuesses);
                        }
                        else if(guessedNumber.toInt() < numbertoGuess) {
                            val toast = Toast.makeText(applicationContext, "The number I chose is larger", Toast.LENGTH_LONG);
                            toast.setGravity(Gravity.CENTER_VERTICAL, 0, 200);
                            toast.show();
                            updateNumberOfGuessesText(numberOfGuessesText, ++numberOfGuesses);
                        }
                        else {
                            numberOfGuesses++;

                            showAlert("You win!", "You guessed in " + numberOfGuesses + " tries")
                            textInput.setText("");
                            numbertoGuess = Random.nextInt(0,20);

                            if (numberOfGuesses == 1) {
                                score += 5;
                            }
                            else if( numberOfGuesses > 1 && numberOfGuesses <= 4) {
                                score += 3;
                            }
                            else if(numberOfGuesses > 4 && numberOfGuesses <= 6) {
                                score += 2;
                            }
                            else if(numberOfGuesses > 7 && numberOfGuesses <= 10) {
                                score += 1;
                            }

                            updateScoreText(scoreText, score);
                            db.updateScore(username, score)

                            numberOfGuesses = 0;
                            updateNumberOfGuessesText(numberOfGuessesText, numberOfGuesses);
                        }
                    }
                    else {
                        showAlert("You lost!", "You didn't guess the number in 10 tries")
                        textInput.setText("")
                        numbertoGuess = Random.nextInt(0,20);
                        numberOfGuesses = 0;
                        updateNumberOfGuessesText(numberOfGuessesText, numberOfGuesses);
                    }
                }
                else {
                    showAlert("Error", "You shall give a number from 0 to 20")
                    textInput.setText("");
                }
            }
            catch (e: NumberFormatException) {
                showAlert("Error", "You shall give a number")
                textInput.setText("");
            }
        }

        newGameButton.setOnClickListener() {
            numbertoGuess = Random.nextInt(0,20);
            numberOfGuesses = 0;
            updateNumberOfGuessesText(numberOfGuessesText, numberOfGuesses);
            textInput.setText("");
        }

        scoreboardButton.setOnClickListener() {
            val intent = Intent(this, ScoreboardActivity::class.java)
            startActivity(intent)
        }
    }

    fun showAlert(title: String, message: String){
        val builder = AlertDialog.Builder(this@MainActivity)
        builder.setTitle(title)
        builder.setMessage(message)

        builder.setPositiveButton("OK"){ _: DialogInterface, _: Int ->}

        val dialog: AlertDialog = builder.create()
        dialog.show()
    }

    fun updateNumberOfGuessesText(view: TextView, guesses: Int) {
        view.setText("Number of guesses: " + guesses);
    }

    fun updateScoreText(view: TextView, score: Int) {
        view.setText("Score: " + score);
    }
}