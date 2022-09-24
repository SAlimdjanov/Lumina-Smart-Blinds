#include <SolarBlinds.h>

void SolarBlinds::initialize(void) {
    usbSerial = new USBSerial();
    usbSerial->initialize();
    stepMotor = new StepMotor();
    stepMotor->initialize();
    stepMotor->turn(500, 0);
}

void SolarBlinds::run(void) {}