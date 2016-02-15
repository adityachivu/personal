import sys
import tty
import termios
import tkSnack
import Tkinter
import os
import datetime

def playnote(freq, duration):
	snd = tkSnack.Sound()
	filt = tkSnack.Filter('generator',freq, 30000, 0.0, 'sine', int(10000*duration))
	snd.stop()
	snd.play(filter = filt, blocking = 1)

root = Tkinter.Tk()
tkSnack.initializeSnack(root)
playnote(float(sys.argv[1]),float(sys.argv[2]))


