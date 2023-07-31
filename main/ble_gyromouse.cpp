#include "ble_gyromouse.h"

const std::string deviceName = "GyroMouse";
const std::string deviceManufacturer = "SunnySnails";
uint16_t vid       = 0x05ac;
uint16_t pid       = 0x820a;
uint16_t version   = 0x0210;


void BleGyroMouse::onDisconnect(BLEServer* pServer) {
  this->connected = false;
}
void BleGyroMouse::onConnect(BLEServer* pServer) {
  this->connected = true;
}
void BleGyroMouse::onWrite(BLECharacteristic* me) {
  uint8_t* value = (uint8_t*)(me->getValue().c_str());
}

bool BleGyroMouse::isConnected(void) {
  return this->connected;
}

void BleGyroMouse::send_keyboard_report(uint8_t* buf){
  //this->inputKeyboard->setValue(buf, keyboard_report_len);
  //this->inputKeyboard->notify();
  this->inputKeyboard->notify(buf, keyboard_report_len);
  // XXX  turn this into a queue and task
  vTaskDelay(2/portTICK_PERIOD_MS); // Delay between loops to reset watchdog timer
}
void BleGyroMouse::send_mouse_report(uint8_t* buf){
  //this->inputMouse->setValue(buf, mouse_report_len);
  //this->inputMouse->notify();
  this->inputMouse->notify(buf, mouse_report_len);
  // XXX  turn this into a queue and task
  vTaskDelay(2/portTICK_PERIOD_MS);
  // XXX buf is either keyboard_report_len or
  //     mouse_report_len, both are 7 bytes

}


void BleGyroMouse::begin(void)
{
  BLEDevice::init(deviceName);
  BLEServer* pServer = BLEDevice::createServer();
  pServer->setCallbacks(this);

  hid = new BLEHIDDevice(pServer);

  inputKeyboard = hid->inputReport(KEYBOARD_KEYS_ID);
  outputKeyboard = hid->outputReport(KEYBOARD_LIGHTS_ID);
  inputMediaKeys = hid->inputReport(MEDIA_ID);
  inputMouse =  hid->inputReport(MOUSE_ID);

  outputKeyboard->setCallbacks(this);

  hid->manufacturer()->setValue(deviceManufacturer);

  hid->pnp(0x02, vid, pid, version);
  hid->hidInfo(0x00, 0x01);

  BLEDevice::setSecurityAuth(true, true, true);

  hid->reportMap((uint8_t*)hid_report_descriptor, hid_report_descriptor_size);
  hid->startServices();

  onStarted(pServer);

  advertising = pServer->getAdvertising();
  advertising->setAppearance(HID_KEYBOARD);
  advertising->addServiceUUID(hid->hidService()->getUUID());
  advertising->setScanResponse(false);
  advertising->start();
  hid->setBatteryLevel((uint8_t) 100);

  ESP_LOGD(LOG_TAG, "Advertising started!");
}
