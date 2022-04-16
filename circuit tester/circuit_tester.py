#Python 3.9
import RPi.GPIO as GPIO
import time

#The following script uses a truth table to test a rudimentary circuit I constructed several years ago. The circuit 
#has a 2-bit memory made of flip-flops, which store opcode instructions. These instructions tell the data register to
#store 0, 1, or tell the adder to add 0+1, or 1+1. It will perform each of these operations and check to make sure the 
#circuit puts out the right values, by controlling the pulse of the clock and reading values of each port. It accomplishes
#this using the general purpose IO on a Raspberry Pi. 
#The program will print out a description of the test progress as it goes along, and at the end will show a count of how
#many errors occurred.

#boolean for the clock port. False = low
clockState = False

# GPIO Pin Assignment
clk = 19  #clock
mem0 = 17 #Memory flip flops
mem1 = 27
ip = 22   #Instruction Pointer register
dat = 5   #Data register
cache0 = 6  #Adder cache
cache1 = 13

#This dictionary will store the inputs from the circuit
input_table = {ip: False, dat: False, cache0: False, cache1: False} 
#This dictionary stores the names of each register
name_table = {ip: "Instruction ptr", dat: "Data register", cache0: "Adder cache 0", cache1: "Adder cache 1"}

#Truth tables: Steps through (mem0, mem1) being (0, 0), (0, 1), (1, 0), and (1, 1) respectively.
#The information in the table should match the input_table data after the mem values are pushed
#to the circuit, and the clock hits a rising edge
truth_table = [
    ("0, 0", {ip: False, dat: False, cache0: False, cache1: True}),
    ("0, 1", {ip: False, dat: True, cache0: False, cache1: True}),
    ("1, 0", {ip: False, dat: True, cache0: True, cache1: False}),
    ("1, 1", {ip: False, dat: True, cache0: True, cache1: False})
]

#Setup GPIO pins
GPIO.setmode(GPIO.BCM)

GPIO.setup(clk, GPIO.OUT)
GPIO.setup(mem0, GPIO.OUT)
GPIO.setup(mem1, GPIO.OUT)
GPIO.setup(ip, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(dat, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(cache0, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(cache1, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

GPIO.output(clk, clockState)
GPIO.output(mem0, 0)
GPIO.output(mem1, 0)

error_count = 0
for sub_table in truth_table:
    print("\n" + "=" * 35)
    #print memory values for current test
    print("Flip-flop memory values for trial: " + sub_table[0]) 
    #synchronize with the instruction pointer. await ip == 0. It will be set on a certain falling edge of a clock cycle.
    print("Synchronizing with Instruction Pointer...")
    while not GPIO.input(ip) == False:
        clockState = not clockState
        GPIO.output(clk, clockState)
        time.sleep(0.1)
    #push memory values to flip flops
    print("Pushing new memory values...")
    GPIO.output(mem0, int(sub_table[0][0]))
    GPIO.output(mem1, int(sub_table[0][3]))
    print("Awaiting 2 high clock edges... (full system cycle)\n\nResults:\nPort             Status  Expected")
    #wait for circuit to process 
    for x in range(4):
        clockState = not clockState
        GPIO.output(clk, clockState)
        time.sleep(0.1)
    #Clock should be low now.
    
    #Read values of GPIO. See if they match truth table
    for port in input_table: 
        #Get the name of the current port as a string
        port_name = list("." * 17)
        for x in range (len(name_table[port])):
            port_name[x] = name_table[port][x]
        #Record status of each port
        input_table[port] = bool(GPIO.input(port))

        if input_table[port]:
            status = "HIGH"
        else:
            status = "LOW "
        #Print the port, its status, and validity
        print(('').join(port_name) + status, end='')
        if input_table[port] == sub_table[1][port]:
            print(" :  Yes")
        else:
            print(" :  No")
            error_count = error_count + 1
    print("=" * 35 + "\n")
    
print("Total errors: " + str(error_count) + "\n")

GPIO.cleanup()