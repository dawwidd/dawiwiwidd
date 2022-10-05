import sqlite3

import RPi.GPIO as GPIO
from random import randrange
from time import sleep  # this lets us have a time delay (see line 15)
import sqlite3 as sql

punktyA = 0
punktyB = 0
skuchyA = 10
skuchyB = 10
winning_points = 2

class Button:
    def __init__(self, BUTTON_PIN, LED_PIN):
        self.BUTTON_PIN = BUTTON_PIN
        self.LED_PIN = LED_PIN

    def set_up(self):
        GPIO.setup(self.BUTTON_PIN, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
        GPIO.setup(self.LED_PIN, GPIO.OUT)  # set GPIO24 as an output (LED)

    def button_click(self, timer):
        timer = int(timer * 1000)
        for i in range(timer):
            sleep(0.001)
            if GPIO.input(self.BUTTON_PIN):
                GPIO.output(self.LED_PIN, 0)
                sleep(1)
                return 1
            else:
                GPIO.output(self.LED_PIN, 1)
        return 0

    def turn_off(self):
        GPIO.output(self.LED_PIN, 0)

    def turn_on(self):
        GPIO.output(self.LED_PIN, 1)

def insertScore(player1, player2, winner):
    con = sqlite3.connect('whackamole.db')
    cur = con.cursor()

    cur.execute('INSERT INTO gry_multiplayer(player1, player2, winner) VALUES(?, ?, ?)',
                (player1, player2, winner))
    con.commit()

    cur.close()
    con.close()

def button_click_multi(buttonA, buttonB, timer):
    global punktyA
    global punktyB
    global skuchyA
    global skuchyB
    flag = 0
    timer = int(timer * 1000)
    for i in range(timer):
        sleep(0.001)
        if GPIO.input(buttonA.BUTTON_PIN):
            GPIO.output(buttonA.LED_PIN, 0)
            GPIO.output(buttonB.LED_PIN, 0)
            sleep(1.5)
            punktyA += 1
            break
        elif GPIO.input(buttonB.BUTTON_PIN):
            GPIO.output(buttonA.LED_PIN, 0)
            GPIO.output(buttonB.LED_PIN, 0)
            sleep(1.5)
            punktyB += 1
            break
        else:
            GPIO.output(buttonA.LED_PIN, 1)
            GPIO.output(buttonB.LED_PIN, 1)

def gameloop_multiplayer(player1, player2):
    GPIO.setmode(GPIO.BCM)  # set up BCM GPIO numbering
    # set GPIO25 as input (button)
    global punktyA
    global punktyB
    global skuchyA
    global skuchyB

    Buttons = [[Button(23,18), Button(16,12)],
               [Button(15,14), Button(21,20)],
               [Button(25,24), Button(17,4)],
               [Button(8,7), Button(22,27)],
               [Button(9,10), Button(5,11)]]

    for button_pair in Buttons:
        for button in button_pair:
            button.set_up()

    print(player1, player2)

    con = sqlite3.connect("whackamole.db")
    cur = con.cursor()
    # try:
        # login = input("Podaj login:");
    while True:  # this will carry on until you hit CTRL+C
        which_button = int(randrange(1, 15))
        print(which_button)
        czas = randrange(5, 15) / 10
        if which_button == 1:
            button_click_multi(Buttons[0][0], Buttons[0][1], czas)
            if punktyA >= winning_points or punktyB >= winning_points:
                break
            print("guzik 1: ", punktyA, punktyB)
        elif which_button == 2:
            button_click_multi(Buttons[1][0], Buttons[1][1], czas)
            if punktyA >= winning_points or punktyB >= winning_points:
                break
            print("guzik 2: ", punktyA, punktyB)
        elif which_button == 3:
            button_click_multi(Buttons[2][0], Buttons[2][1], czas)
            if punktyA >= winning_points or punktyB >= winning_points:
                break
            print("guzik 3: ", punktyA, punktyB)
        elif which_button == 4:
            button_click_multi(Buttons[3][0], Buttons[3][1], czas)
            if punktyA >= winning_points or punktyB >= winning_points:
                break
            print("guzik 4: ", punktyA, punktyB)
        elif which_button == 5:
            button_click_multi(Buttons[4][0], Buttons[4][1], czas)
            if punktyA >= winning_points or punktyB >= winning_points:
                break
            print("guzik 5: ", punktyA, punktyB)
        else:
            for button_pair in Buttons:
                for button in button_pair:
                    button.turn_off()
        sleep(czas)  # wait 0.1 seconds
    winner = "Remis"
    if punktyA >= winning_points:
        winner = player1
    elif punktyB >= winning_points:
        winner = player2
    print("Wygrał gracz:", winner)

    # finally:  # this block will run no matter how the try block exits
    for i in range(10):
        for button_pair in Buttons:
            for button in button_pair:
                button.turn_on()
        sleep(0.25)
        for button_pair in Buttons:
            for button in button_pair:
                button.turn_off()
        sleep(0.25)
    GPIO.cleanup()  # clean up after yourself
    insertScore(player1, player2, winner)
    return winner 
