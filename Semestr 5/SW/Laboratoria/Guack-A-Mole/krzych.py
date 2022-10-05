 
import sqlite3

import RPi.GPIO as GPIO
from random import randrange
from time import sleep  # this lets us have a time delay (see line 15)
import sqlite3 as sql


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


def gameloop():
    GPIO.setmode(GPIO.BCM)  # set up BCM GPIO numbering
    # set GPIO25 as input (button)

    button1a = Button(23, 18)
    button1a.set_up()
    button1b = Button(16, 12)
    button1b.set_up()

    button2a = Button(15, 14)
    button2a.set_up()

    button3a = Button(25, 24)
    button3a.set_up()

    button4a = Button(8, 7)
    button4a.set_up()
    # con = sqlite3.connect("whackamole.db")
    # cur = con.cursor()

    punkty = 0
    skuchy = 10
    try:
        # login = input("Podaj login:");
        while True:  # this will carry on until you hit CTRL+C
            which_button = int(randrange(1, 10))
            print(which_button)
            czas = randrange(5, 15) / 10
            if which_button == 1:
                punkt = button1a.button_click(czas)
                punkt = button1b.button_click(czas)
                if punkt:
                    punkty += 1
                else:
                    skuchy -= 1
                    if skuchy < 1:
                        break
                print("guzik 1: ", punkty)
            elif which_button == 2:
                punkt = button2a.button_click(czas)
                if punkt:
                    punkty += 1
                else:
                    skuchy -= 1
                    if skuchy < 1:
                        break
                print("guzik 2: ", punkty)
            elif which_button == 3:
                punkt = button3a.button_click(czas)
                if punkt:
                    punkty += 1
                else:
                    skuchy -= 1
                    if skuchy < 1:
                        break
                print("guzik 3: ", punkty)
            elif which_button == 4:
                punkt = button4a.button_click(czas)
                if punkt:
                    punkty += 1
                else:
                    skuchy -= 1
                    if skuchy < 1:
                        break
                print("guzik 4: ", punkty)
            else:
                button1a.turn_off()
                button1b.turn_off()
                button2a.turn_off()
                button3a.turn_off()
                button4a.turn_off()
                sleep(1)
            sleep(randrange(5, 10) / 100)  # wait 0.1 seconds

    finally:  # this block will run no matter how the try block exits
        # cur.execute(
        #     "INSERT INTO gry_singleplayer(wynik, gracze_id_gracza) VALUES(?, (SELECT id_gracza FROM gracze WHERE login LIKE ?))",
        #     (punkty, login))
        print("Jesteś życiową porażką")
        print("Zdobyłeś", punkty, "punktów")
        for i in range(10):
            button1a.turn_on()
            button1b.turn_on()
            button2a.turn_on()
            button3a.turn_on()
            button4a.turn_on()
            sleep(0.25)
            button1a.turn_off()
            button1b.turn_off()
            button2a.turn_off()
            button3a.turn_off()
            button4a.turn_off()
            sleep(0.25)
        # con.commit()
        # con.close()
        GPIO.cleanup()  # clean up after yourself


gameloop()
