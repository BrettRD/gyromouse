
#ifndef ESP32_BLE_GYROMOUSE_H
#define ESP32_BLE_GYROMOUSE_H

#include <NimBLEDevice.h>
#include <NimBLEServer.h>
#include <NimBLEUtils.h>
#include <NimBLEHIDDevice.h>


#include "NimBLECharacteristic.h"
#include "NimBLEHIDDevice.h"
#define BLEDevice                  NimBLEDevice
#define BLEServerCallbacks         NimBLEServerCallbacks
#define BLECharacteristicCallbacks NimBLECharacteristicCallbacks
#define BLEHIDDevice               NimBLEHIDDevice
#define BLECharacteristic          NimBLECharacteristic
#define BLEAdvertising             NimBLEAdvertising
#define BLEServer                  NimBLEServer


#include "hid_report.h"
#include <cstring>


void init_gryomouse_ble(void);

class BleGyroMouse : public BLEServerCallbacks, public BLECharacteristicCallbacks
{
private:
  BLEHIDDevice* hid;
  BLECharacteristic* inputKeyboard;
  BLECharacteristic* outputKeyboard;
  BLECharacteristic* inputMediaKeys;
  BLECharacteristic* inputMouse;

  BLEAdvertising*    advertising;

  bool connected = false;

public:
  void begin(void);
  bool isConnected(void);

  void send_keyboard_report(uint8_t* buf);
  void send_mouse_report(uint8_t* buf);

protected:
  // create the necessary the callbacks for BLEServerCallbacks and BLECharacteristicCallbacks
  virtual void onStarted(BLEServer *pServer) { };
  virtual void onConnect(BLEServer* pServer) override;
  virtual void onDisconnect(BLEServer* pServer) override;
  virtual void onWrite(BLECharacteristic* me) override;

};


#endif // ESP32_BLE_GYROMOUSE_H