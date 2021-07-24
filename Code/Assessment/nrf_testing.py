import serial
import time
import numpy as np
import os

with open('C://DATA//Git//Flowmeter-Alert//Code//Final_Testing_Scripts//nrf_trans_output.txt', 'w') as fp:
    pass

with open('C://DATA//Git//Flowmeter-Alert//Code//Final_Testing_Scripts//nrf_rece_output.txt', 'w') as fp:
    pass
transmitter = serial.Serial('COM4', 9600, timeout=1)
receiver = serial.Serial('COM11', 9600, timeout=1)

while (1==1):
    # transmitter.reset_input_buffer()
    
    try:
        tran_str = transmitter.readline().decode('utf-8')
        with open("C://DATA//Git//Flowmeter-Alert//Code//Final_Testing_Scripts//nrf_trans_output.txt", "a") as myfile:
            print(tran_str)
            myfile.write(tran_str)
    except:
        pass
    
    # receiver.reset_input_buffer()
    try:
        rece_str = receiver.readline().decode('utf-8')
        with open("C://DATA//Git//Flowmeter-Alert//Code//Final_Testing_Scripts//nrf_rece_output.txt", "a") as myfile:
            print(rece_str)
            myfile.write(rece_str)
    except:
        pass
        