#include <Subsystems/USBSerial/USBSerial.h>

void USBSerial::initialize(void) { Serial.begin(SERIAL_BAUD_RATE); }

int USBSerial::write(std::string message) {
    Serial.write(message.c_str());
    return 0;
}

int USBSerial::read(void) { return Serial.read(); }

int USBSerial::available(void) { return Serial.available(); }