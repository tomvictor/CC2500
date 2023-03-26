# Wireless communication using CC2500
Author: Tomvictor  
Mail: tom@buildfromzero.com  

![CC2500](rx-tx.png "cc2500 - buildfromzero.com")


This is a simple program for implementing wireless communication, rssi calculation using cc2500 rf module from texas instruments
In this project I am measuring accelarometer data using MSP430G2553 and send to other msp controller wirelessly with the help of cc2500.
here I am using adxl335 as accelarometer, 16 x 2 lcd module. I thing this will be a good example for starting projects in wireless
electronics. 
rssi calculation is done n the rx section(by directly reading a register, look datasheet for more details)
accelarometer make use of ADC
I am sending the accelarometer data + MSP430 internal temprature + an continously incrementing varable in transmitter.
and the same is receiving on the other end.
The code is completely working
