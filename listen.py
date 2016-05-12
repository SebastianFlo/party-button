# Listen to the arduino input and open a browser
import serial
import webbrowser

myPort = "/dev/ttyACM0"
baudRate = 9600
ser = serial.Serial(myPort, baudRate)

previousMode = 0

while 1:
    output = ser.readline()
    # check only for data that has: 'status'
    status = output.split(":")
    if status[0].rstrip() == "status":
        # convert to in
        mode = int(status[1].rstrip())
        # if state change
        if mode != previousMode:
            # if turning on
            if mode:
                print("Mode is on: %s" % mode)
                url = "http://youtube.com"
                webbrowser.open(url)
            # if turning off   
            if not mode:
                print("Mode is off: %s" % mode)
            previousMode = mode
