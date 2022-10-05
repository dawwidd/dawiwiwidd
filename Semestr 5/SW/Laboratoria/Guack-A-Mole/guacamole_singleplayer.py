import sqlite3

import RPi.GPIO as GPIO
from random import randrange
from time import sleep

punkty = 0
winning_points = 10000
skuchy = 3

class Button:
    def __init__(self, BUTTON_PIN, LED_PIN):
        self.BUTTON_PIN = BUTTON_PIN
        self.LED_PIN = LED_PIN

    def set_up(self):
        GPIO.setup(self.BUTTON_PIN, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
        GPIO.setup(self.LED_PIN, GPIO.OUT)  # set GPIO24 as an output (LED)

    def button_click(self, timer):
        timer = int(timer * 1000)
        global punkty
        global skuchy
        for i in range(timer):
            sleep(0.001)
            if GPIO.input(self.BUTTON_PIN):
                GPIO.output(self.LED_PIN, 0)
                punkty += 1
                skuchy += 1
                break
            else:
                GPIO.output(self.LED_PIN, 1)
        skuchy -= 1
        print('Punkty', punkty)
        print('Skuchy', skuchy)
        return

    def turn_off(self):
        GPIO.output(self.LED_PIN, 0)

    def turn_on(self):
        GPIO.output(self.LED_PIN, 1)


def insertScore(player, score):
    con = sqlite3.connect('whackamole.db')
    cur = con.cursor()

    cur.execute('INSERT INTO gry_singleplayer(player, score) VALUES(?, ?)', (player, score))
    con.commit()

    cur.close()
    con.close()

def gameloop_singleplayer(player):
    GPIO.setmode(GPIO.BCM)  # set up BCM GPIO numbering
    # set GPIO25 as input (button)
    global punkty
    global skuchy

    Buttons = [Button(23,18),
               Button(15,14),
               Button(25,24),
               Button(8,7),
               Button(9,10)]


    for button in Buttons:
        button.set_up()

    print(player)

    # try:
        # login = input("Podaj login:");
    while True:  # this will carry on until you hit CTRL+C
        which_button = int(randrange(1, 15))
        print(which_button)
        czas = randrange(5, 15) / 10
        if which_button == 1:
            Buttons[0].button_click(czas)
            if punkty >= winning_points or skuchy < 1:
                break
            # print("guzik 1: ", punkty)
        elif which_button == 2:
            Buttons[1].button_click(czas)
            if punkty >= winning_points or skuchy < 1:
                break
            # print("guzik 2: ", punkty)
        elif which_button == 3:
            Buttons[2].button_click(czas)
            if punkty >= winning_points or skuchy < 1:
                break
            # print("guzik 3: ", punkty)
        elif which_button == 4:
            Buttons[3].button_click(czas)
            if punkty >= winning_points or skuchy < 1:
                break
            # print("guzik 4: ", punkty)
        elif which_button == 5:
            Buttons[4].button_click(czas)
            if punkty >= winning_points or skuchy < 1:
                break
            # print("guzik 5: ", punkty)
        else:
            for button in Buttons:
                button.turn_off()
        sleep(czas)  # wait 0.1 seconds
    if skuchy < 1: print("Jak mogłeś w to przegrać lol")

    # finally:  # this block will run no matter how the try block exits
    for i in range(10):
        for button in Buttons:
            button.turn_on()
        sleep(0.25)
        for button in Buttons:
            button.turn_off()
        sleep(0.25)

    GPIO.cleanup()  # clean up after yourself

    print('Punkty', punkty)
    insertScore(player, punkty)
    return punkty
