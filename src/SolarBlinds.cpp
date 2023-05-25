#include <SolarBlinds.h>

// Change to true to use Wi-Fi
const bool USE_WIFI = true;

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
        wiFiHTTCP = new WiFiHTTCP();
        wiFiHTTCP->initialize();
        scpiListener->addNewInterface(wiFiHTTCP->getTCPClient());
    }
}

void SolarBlinds::run(void) {
    // Run Stepper Motor
    stepperMotor->runStepper();
    // Listen for SPCI commands
    scpiListener->listenForCommand();
    // Continuously check Wi-Fi connection and data updates
    if (USE_WIFI) {
        SolarBlinds::wiFiHTTCP->checkConnection();
    }
}