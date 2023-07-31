# Gyromouse

A complete and truly portable computer interface device.

This is a chording keyboard inspired by the Twiddler 3, with a few additions and changes to make it more practical

## Project Goals:
* Reduce shoulder pain from palms-down interfaces
* Works where mice don't work and keyboards don't fit
* Scroll PDFs on weird screens
* Extensible into robotics applications
* 

## Mouse
This controller uses a gyro to handle mouse input, much like gyro aiming in video games.

## Scroll
One of the main use of this keyboard is to scroll through PDFs.
The scroll action is implemented as the touch input from a LCD.

## Keymap
This controller allows users to do interesting things to the keymap

### Media keys
The HID table is exposed to the user, allowing the user to send events on against wide variety of features from HID


### Dwell chords
Certain chords are subsets of other chords, dwell allows you to release parts of a chord as one keystroke, wait a fraction of a second, then release the rest as another keystroke




# Issues:

## LCD
Needs a whole UI system

## Capacitive Touch Input
strongly coupled to LCD lib

## Bluetooth
NimBLE for esp32 cpp needs testing with the existing calls.

## IMU
Needs a MPU9250 driver, and there are so many shit ones it's easier to write a new one than find a good one

## Key matrix
I2C stubs need adapting esp-idf.



# Wishlist
## Keyboard Layers
optimised keymaps for specific data entry tasks

## Non-Chording Layer
Arrow keys/numpad with OS-side auto-repeat

## Internal notes
Text entry to internal storage. 
interpret keyscan into ascii so you don't accidentally rubber-ducky yourself

* Web UI to pick up the files
* LVGL tools to add a note browsing UI
* Expose files as USB drive

## Stereo Microphone
A mic input allows the device to participate in an audionav constellation, and offer absolute position input.

### Laser
Presentation pointer (but I have a cursor?)

## WiFi
The application processor has wifi, allowing the keyboard to act as an input device for niche communication systems.

### Express LRS
Control drones or at least send and receive telemetry data

### Micro ROS over EmbeddedRTPS or E-LRS
Send commands to a ROS graph
Send absolute pose to a moveit follow / grasp config

## Storage
Stores encrypted and auto-synced files between computers
Portable boot drive


# TODO
Convert whole project to ESP-IDF

## Remove Arduino contamination

### Main
re-combine setup and loop, establish rtos tasks - done

### delay / micros
Implement a message queue between application code and BLE message handlers with a rate limit on messages

remove calls to micros, use native timing system - done

### Serial
remove calls to serial, convert to a macro-ed debug call

no existing print calls

### DigitalRead, pinMode
remove digitalRead, use native GPIO accessors - done (check)

### IMU
Wire IMU onto SPI port

### Peripheral monitoring
Split IMU and keyscan monitoring out to separate tasks - done

### Wire lib for I2C
Need to configure I2C

## Bluetooth:
https://github.com/h2zero/esp-nimble-cpp

cloned, needs config

## LCD
https://docs.lvgl.io/master/get-started/platforms/espressif.html#using-lvgl-esp32-drivers-in-esp-idf-project

cloned, needs config

## IMU
Split register map and accessors to separate files
### UncleRus
Take another look at https://github.com/UncleRus/esp-idf-lib
XXX Does not have MPU9250, but that needs building anyway
XXX Does not state S3 support

## Sleep
Devise an entry into a low power mode

## BLE Mouse separate move and scroll endpoints?
The trackpad and gyro are not synchronised inputs.
Can they be sent to different endpoints in HID?
