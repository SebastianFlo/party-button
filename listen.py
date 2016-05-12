import serial
import webbrowser
import os
# Set correct browser to open and close
# browserExe = "chromium-browse"
browserExe = "Google Chrome"

#myPort = "/dev/ttyACM0"
myPort = "/dev/cu.usbmodem1421"
baudRate = 9600
# python serial will need to be downloaded and python setup.py install 
ser = serial.Serial(myPort, baudRate)

previousMode = 0

while 1:
    output = ser.readline()
    #check only for data that has: 'status'
    status = output.split(":")
    if status[0].rstrip() == "status":
        # convert to in
        mode = int(status[1].rstrip())
        # if state change
        if mode != previousMode:
            # if turning on
            if mode:
                print("Mode is on: %s" % mode)
                url = "https://www.youtube.com/watch?v=uSD4vsh1zDA&list=PLEA119CBC8AC8E74D"
                webbrowser.open(url)
            # if turning off   
            if not mode:
                print("Mode is off: %s" % mode)
                # os.system("pkill " + browserExe)
		os.system("kill -9 " + browserExe) 
            previousMode = mode
