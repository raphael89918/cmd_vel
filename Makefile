ARDUINO_DIR = /usr/share/arduino
ARDMK_DIR = /usr/share/arduino


USER_LIB_PATH := $(realpath ./libraries)
ARDUINO_LIB_PATH := $(realpath ./libraries)

BOARD_TAG    = mega2560
MONITOR_PORT = /dev/ttyACM0
MNITOR_BAUDRATE = 57600
ARDUINO_SKETCHBOOK := $(realpath ./libraries)
CXXFLAGS_STD = -std=gnu++14

ARDUINO_LIBS += ros_lib
include $(ARDMK_DIR)/Arduino.mk
