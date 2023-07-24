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

## Trackball
The Pimoroni Trackball loses more than half of the user inputs to mechanical crunchyness. The on-board firmware has fatal issues with up-time and low-power modes.
The Pimoroni trackball is removed in favour of the capacitive touch layer on a TFT LCD

## LCD
LVGL uses TFT_eSPI as driver
TFT_eSPI does not build for arduino without lib tampering because arduino's build chain sucks (doesn't pass user defines to lib headers)

## Capacitive Touch Input
Not yet implemented, likely strongly coupled to choice of LCD lib

## Bluetooth
NimBLE was not obviously functional for ESP32 when I first approached it, so the project got built for arduino.

## IMU
MPU9250 drivers are not generally high quality, and not sensibly available for esp32, (I've written three IMU drivers, and I'm sick of it.)

## Toolchain
The major open toolchains for MCUs struggle to get quality contributions, and end up with a very high API churn.

## Key matrix
No issues, the I2C stubs will need adapting for a toolchain change.



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
re-combine setup and loop, establish rtos tasks

### delay / micros
Implement a message queue between application code and BLE message handlers with a rate limit on messages

remove calls to micros, use native timing system

### Serial
remove calls to serial, convert to a macro-ed debug call

### DigitalRead, pinMode
remove digitalRead, use native GPIO accessors

### IMU
Wire IMU onto SPI port

### Peripheral monitoring
Split IMU and keyscan monitoring out to separate tasks


## Bluetooth:
https://github.com/h2zero/esp-nimble-cpp

## LCD
https://docs.lvgl.io/master/get-started/platforms/espressif.html#using-lvgl-esp32-drivers-in-esp-idf-project

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
