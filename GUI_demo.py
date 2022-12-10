import tkinter.messagebox
from tkinter import *
from tkinter import ttk
import ur_control as urc
import serial
import sys
import glob
import time
# create tkinter instance
root=Tk()
# set window title
root.title('Green House pollination Demo')
#set window size
root.minsize(width=500,height=500)
# define work area
mainframe=ttk.Frame(root)
mainframe.grid(row=5,column=5)

#serial communication
if sys.platform.startswith('win'):
    ports = ['COM%s' % (i + 1) for i in range(256)]
elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
    print("we got linux")
    # this excludes your current terminal "/dev/tty"
    ports = glob.glob('/dev/tty[A-Za-z]*')
elif sys.platform.startswith('darwin'):
    ports = glob.glob('/dev/tty.*')
else:
    print('Unsupported platform')

result = []
'''for port in ports:
    try:
        s = serial.Serial(port)
        s.close()
        result.append(port)
    except (OSError, serial.SerialException):
        pass
'''
print("available ports",result)

ser =""
def connect():
    global ser,port_str
    #port=port_str.get()  # check which port was really used
    port='/dev/ttyUSB0'
    port2='/dev/ttyUSB2'
    try:
    	ser=serial.Serial()
    	ser.budrate=9600#115200
    	ser.port=port
    	ser = ser.open() # open serial port
    except:
    	ser.port=port2  # open serial port
    	ser.open()
    time.sleep(0.2)
    return ser



# define functions for buttons
def t_Demo1():
    # all the way forward
    # all the way backward
    # repeat once
    ser=connect()
    ser.write(b'[D1]')
    pass
def t_Demo2():
    # all the way forward but with pause
    # all the way backward but with pause
    # repeat once
    ser=connect()
    ser.write(b'[D2]')
    pass
def f_demo():
    tkinter.messagebox.showinfo(' Information',' For the full demo run the matlab code')
    pass
def d_Demo():
    # move robotic arm to multiple all 4 quadrant and back to home
    # then move the trolley forward
    # repeat once
    ser=connect()
    for i in range(10):
    	ser.flush()
    	ser.write(data=b'[D3]\n')
    
    #set feedback activation
    for i in range(10):
    	time.sleep(2.1)
    	urc.go_home()
    	urc.go_g1()
    	urc.go_q2()
    	urc.go_q3()
    	urc.go_q4()
    pass


# Define Buttons
fonts=('Times',30)
td1=Button(mainframe,text='Trolley Demo 1',font=fonts,command=t_Demo1).grid(column=1,row=2,padx=10,pady=100)
td2=Button(mainframe,text='Trolley Demo 2',font=fonts,command=t_Demo2).grid(column=4,row=2,padx=10,pady=100)
td3=Button(mainframe,text='Full Demo',font=fonts,command=f_demo).grid(column=1,row=4,padx=10,pady=100)
td4=Button(mainframe,text='Dummy Demo',font=fonts,command=d_Demo).grid(column=4,row=4,padx=10,pady=100)

port_str=StringVar()
#inital text
port_str.set("Select Port")
p_drop=OptionMenu(mainframe,port_str,result).grid(column=3,row=5)
#td1.pack()
#td2.pack()



# show tkinter window
root.mainloop()
