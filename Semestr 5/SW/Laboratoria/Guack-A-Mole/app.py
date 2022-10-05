 
from flask import Flask, render_template, flash, redirect, url_for, request
from guacamole_multiplayer import gameloop_multiplayer
from forms import startMultiplayerForm
# import mysql.connector
# from mysql.connector import Error

app = Flask(__name__)

app.config['SECRET_KEY'] = 'e185681a407ace961e0bf2fdcdced1c7'


@app.route('/')
def home():
    form = startMultiplayerForm()
    return render_template('home.html', form = form)


@app.route('/game', methods=['GET','POST'])
def game():
    if request.method == 'POST':
        gameloop_multiplayer()
        return redirect(url_for('game'))
    return render_template('game.html')

# @app.route()

if __name__ == '__main__':
    app.run(debug=True, host='192.168.1.10', port=8080, threaded=False)
