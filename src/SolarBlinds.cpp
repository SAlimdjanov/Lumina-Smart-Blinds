#include <SolarBlinds.h>

// Comment out to use without Wi-Fi
const bool USE_WIFI = false;

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
    // // Initialize Wi-Fi, if enabled
    if (USE_WIFI) {
        wiFiTCP = new WiFiTCP();
        wiFiTCP->initialize();
        scpiListener->addNewInterface(wiFiTCP->getTCPClient());
    }
}

void SolarBlinds::run(void) {
    // Listen for commands
    scpiListener->listenForCommand();
    // Continuously check Wi-Fi connections
    if (USE_WIFI) {
        SolarBlinds::wiFiTCP->checkConnection();
    }
}