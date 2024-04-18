
# MINIFAB DAEMON

import os, time


pin_mapping = { '7':'71', '11':'78', '13':'76', '15':'74', '19':'231', '21':'232', '23':'230', '35':'198', '37':'79', '12':'77', '16':'75', '18':'73', '26':'200', '32':'201', '38':'234', '40':'72' }

def digitalWrite(pin, state):
    cmd = "sudo gpioset gpiochip0 " + pin_mapping[str(pin)] + "=" + str(state)
    os.system(cmd)

def analogRead(pin):
    return int(os.popen("sudo gpioget gpiochip0 " + pin_mapping[str(pin)]).read())



stop_button_gpio = 11
stopped = False

def start():
    pass

def loop():
    # emergency stop
    global stopped
    if analogRead(stop_button_gpio) == 0 and stopped == False:
        os.system('curl -d "script=M112" http://mfv3.local/printer/gcode/script')
        stopped = True
    else:
        stopped = False

start()
while(True):
    loop()

