ARDMK_DIR           = $(PROJECT_DIR)/lib/makeEspArduino
USER_LIB_PATH       = $(realpath $(PROJECT_DIR)/lib)

BUILD_DIR           = $(PROJECT_DIR)/bin
CHIP                ?= esp8266
BOARD               ?= generic
FLASH_DEF           ?= 512K64
UPLOAD_SPEED        ?= 115200
UPLOAD_RESET        ?= nodemcu
VERBOSE             ?= 1
SKETCH              ?= $(PROJECT_DIR)/src/Arduino.ino

LIBS = $(ESP_LIBS)/Wire \
	$(ESP_LIBS)/ESP8266WiFi \
	$(USER_LIB_PATH)/Adafruit-BMP085-Library \
	$(USER_LIB_PATH)/ArduinoJson/src \
	$(USER_LIB_PATH)/DHT-sensor-library \
	$(USER_LIB_PATH)/LinkedList \
	$(USER_LIB_PATH)/pubsubclient/src \
	$(USER_LIB_PATH)/TSL2561-Arduino-Library \
	$(USER_LIB_PATH)/SimpleTimer

include $(ARDMK_DIR)/makeEspArduino.mk