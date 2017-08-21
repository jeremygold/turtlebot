# Using micropython to build a turtlebot

### Install pip
```
$ sudo easy_install pip
```
### Install esptool
```
$ pip install esptool
```
### Erasing old firmware
```
$ sudo ./esptool.py --port /dev/ttyUSB0 erase_flash
```
### flashing new firmware [source](http://micropython.org/download/#esp8266)

```
$ sudo ./esptool.py --port /dev/ttyUSB0 write_flash --flash_size=8m 0 esp8266-20160809-v1.8.3.bin
```
### Connect a serial port terminal such as minicom or realterm, connect using 115200 baudrate
Confirm you receive a python prompt '>>>'
### install ampy:
```
$ pip install adafruit-ampy
```
### Run a ampy command to check it's working correctly
```
$ sudo ampy --port /dev/ttyUSB0 run test.py
```
### Output:
```
Hello world! I can count to 10:
1
2
3
4
5
6
7
8
9
10
```
### Now copy a main.py which is executed everytime the esp8266 starts up
```
$ sudo ampy --port /dev/ttyUSB0 put blink.py /main.py
```
'Reset' ESP8266 module to start the new program.

### Running the project

You can run the project directly from the atom editor, using platform IO
Firstly you will need to setup the udev rules, and add dial out permissions
for your user

Follow the instructions [here](https://github.com/platformio/platformio-core/blob/develop/scripts/99-platformio-udev.rules)

If you get a compiler error about Base64.h
You may need to edit your Base64.cpp ig it complains about pgmspace
```
$vim .piolibdeps/Base64_ID582/src/Base64.cpp
```

change the line
```
#include <avr/pgmspace.h>
```
to
```
#include <pgmspace.h>
```

### Run the generate_password_cipher.py script and follow the prompts to setup wifi for the module
