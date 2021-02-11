import serial

port = serial.Serial('COM3', 9600)

while True:
    if (port.inWaiting() > 0): 
        print(port.readline())

port.close()