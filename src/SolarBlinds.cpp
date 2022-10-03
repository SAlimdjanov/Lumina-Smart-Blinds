#include <SolarBlinds.h>

void SolarBlinds::initialize(void) {
    // Initialize USB serial communications
    usbSerial = new USBSerial();
    usbSerial->initialize();
    // Initialize stepper motor
    stepperMotor = new StepMotor();
    stepperMotor->initialize();
    // Set up SCPI listening
    scpiListener = new SCPIListener();
    scpiListener->addNewInterface(&Serial);
    // Set up SCPI handler
    scpiHandler = new SCPIHandler(scpiListener);
}

void SolarBlinds::run(void) {
    // Listen for commands
    scpiListener->listenForCommand();
}