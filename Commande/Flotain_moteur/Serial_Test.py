import serial 
import time 


sdata = serial.Serial("/dev/ttyUSB0", 9600, timeout=1.0)

time.sleep(2)

sdata.reset.input.buffer()

print("Arduino Connected")

while (True):
    time.sleep(0.0')
    if sdata.in_waiting > 0 
        mydata = sdata.readLine().decode('utf-8').rstrip()
        print(mydata)
