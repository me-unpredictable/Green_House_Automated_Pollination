import socket
import time

host='192.168.251.12'
port=30002



def ur_control(cmd,exe_time=5):
    connection=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    connection.connect((host,port))

    ret_msg=''
    # send command to the robot
    if(type(cmd)==str):
        cmd=((cmd+"\n").encode("utf8"))

        connection.send(cmd)
        time.sleep(exe_time) # wait for the command execution
        ret_msg=connection.recv(1024)
        ret_msg=repr(ret_msg) # convert the message to a readable text format
    else:
        print("Command Error!!!")

    return ret_msg

# function to change robot position to home

#msg=ur_control('powerdown()')
#print(msg)

#b'\x00\x00\x007\x14\xff\xff\xff\xff\xff\xff\xff\xff\xfe\x03\tURControl\x05\x0c\x00\x00\x00\x02\x00\x00\x00\x0028-06-2022, 11:30:43\x00\x00\x00\x18\x14\xff\xff\xff\xff\xff\xff\xff\xff\xfe\x0c\x00\x00\x00\x00\x00\x00\x00\x00\x01'

def go_home(exe_time=6):
    #set robot to home position
    ur_control('movej([0,-1.57,0,-1.57,0,1.57],a=1.0,v=0.8,t=0,r=0)',exe_time)
def go_q4(exe_time=6):
    #move to 4th quadrent
    ur_control('movej([0,0.47,-2.0,-1.57,0,1.57],a=1,v=0.8,t=0,r=0)',exe_time)
def go_q3(exe_time=6):
    #move to 3th quadrent
    ur_control('movej([0,-3.6,2.0,-1.57,0,1.57],a=1,v=0.8,t=0,r=0)',exe_time)
def go_q2(exe_time=6):
    #move to 2nd quardrent
    ur_control('movej([0,-2.35,0.8,-1.57,0,1.57],a=1,v=0.8,t=0,r=0)',exe_time)
def go_g1(exe_time=6):
    #move to 1st quardrent
    ur_control('movej([0,-0.8,-0.8,-1.57,0,1.57],a=1,v=0.8,t=0,r=0)',exe_time)

