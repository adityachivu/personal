import tkSnack
import Tkinter
import os

def playnote():
	startT = 0
	endT = 132300
	if(os.path.isfile('rainsignal.txt')):
		while(os.path.isfile('rainsignal.txt')):
			snd.play(blocking=1,start=startT,end=endT)
			startT+=132300
			endT+=132300
		snd.stop()
			
root = Tkinter.Tk()
tkSnack.initializeSnack(root)
snd = tkSnack.Sound()
snd.read('rain.wav')
while(1):
	playnote()


