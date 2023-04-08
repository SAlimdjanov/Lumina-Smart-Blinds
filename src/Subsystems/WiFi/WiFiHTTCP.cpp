// #include <Subsystems/StepperMotor/StepperMotor.h>
#include <Subsystems/WiFi/WiFiHTTCP.h>

const char *SSID = "SBlinds";
const char *PASSWORD = "maktal22";

// int currentAngle = 0;

StepMotor *WiFiHTTCP::motor = new StepMotor();

WiFiHTTCP::WiFiHTTCP()
    : TCPClient(new WiFiClient()),
      isWiFiConnected(false),
      lastTCPAttemptTimestamp(0),
      systemLogger(SystemLogger::getLogger()) {}

void WiFiHTTCP::initialize() {
    // maxMeasuredVoltage = motor->calibrationSweep();
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);
    Serial.println("\nConnecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    systemLogger->logInfo(tag, "Connected to Blinds!");
    time = millis() + 1000;  // Delay first get request to avoid init error
}

const long HTTPtimeInterval = 1000;
unsigned long previousHTTPtime = 0;

const long delayedSweepFlagInterval = (3.8) * 1000;
bool delayedSweepFlag = false;
unsigned long previousDelayedSweepFlagtime = 0;

const long getVoltageFlagInterval = (3.8 / 90) * 1000;
bool getVoltageFlag = false;
unsigned long previousGetVoltageFlagTime = 0;
int voltageCounter = 90;

// int angleVoltage[90];

int optimalAngle = 0;
int maxVoltage = 0;

static gpio_num_t READ_VOLTAGE_PIN = GPIO_NUM_34;
uint16_t measuredVoltage = 0;

bool reSyncFlag = true;
int limitSwitchCounter = 0;
unsigned long previouslimitSwitchTime = 1000;
const long degreeInterval = (3.8 / 90) * 1000;

void WiFiHTTCP::checkConnection() {
    isMotorMoving = motor->inMotion();  // Rename? (Functionality may change)

    Serial.println(motor->isAtNinetyDegrees());

    // measuredVoltage = analogRead(READ_VOLTAGE_PIN);
    // Serial.println(measuredVoltage);

    // if (reSyncFlag == true) {
    //     if (limitSwitchCounter <= 120 && !motor->isAtNinetyDegrees()) {
    //         if (millis() - previouslimitSwitchTime >= degreeInterval) {
    //             Serial.println(motor->isAtNinetyDegrees());
    //             motor->turnMotor((400 / 90) * limitSwitchCounter);
    //             limitSwitchCounter++;
    //             previouslimitSwitchTime = millis();
    //             Serial.println(limitSwitchCounter);
    //         }
    //     } else {
    //         reSyncFlag = false;
    //         Serial.println("stopped");
    //     }
    // }

    if (delayedSweepFlag == true) {
        unsigned long currentDelayedSweepFlagtime = millis();
        if (currentDelayedSweepFlagtime - previousDelayedSweepFlagtime >=
            delayedSweepFlagInterval) {
            Serial.println("Motor Moving to 0");
            motor->turnMotor(0);
            delayedSweepFlag = false;

            previousGetVoltageFlagTime = millis();
            getVoltageFlag = true;

            // previousDelayedSweepFlagtime = currentDelayedSweepFlagtime;
        }
    }

    if (getVoltageFlag == true) {
        unsigned long currentGetVoltageFlagTime = millis();
        if (currentGetVoltageFlagTime - previousGetVoltageFlagTime >= getVoltageFlagInterval) {
            if (voltageCounter >= 0) {
                measuredVoltage = analogRead(READ_VOLTAGE_PIN);
                if (measuredVoltage > maxVoltage) {
                    maxVoltage = measuredVoltage;
                    optimalAngle = voltageCounter;
                }
                // angleVoltage[voltageCounter] = measuredVoltage;
                // uint16_t

                Serial.print("Voltage at ");
                Serial.print(voltageCounter);
                Serial.print(" degrees is: ");
                Serial.println(measuredVoltage);
                // Serial.println(random(0,20));
                // measured every 0.42 seconds
                voltageCounter = voltageCounter - 1;
            } else {
                HTTPClient http;

                http.begin(
                    "https://automated-solar-blinds-default-rtdb.firebaseio.com/"
                    "optimalAngle.json");  // Specify the URL
                http.addHeader("Content-Type", "application/json");

                // int optimalAngle = optimal;
                // random number from 0 to 90
                int httpOptimalAngleResponseCode = http.PUT(String(optimalAngle));

                Serial.print("Updated server angle to ");
                Serial.println(optimalAngle);

                http.end();  // Free the resources

                voltageCounter = 90;
                optimalAngle = 0;
                maxVoltage = 0;
                getVoltageFlag = false;
            }

            previousGetVoltageFlagTime = currentGetVoltageFlagTime;
        }
    }

    if (millis() - time >= POLLING_INTERVAL && !isMotorMoving && getVoltageFlag == false) {
        if ((WiFi.status() == WL_CONNECTED)) {
            HTTPClient http;  // Check the current connection status
            http.begin(
                "https://automated-solar-blinds-default-rtdb.firebaseio.com/optimalAngleFlag/"
                "FlagSet.json");        // Specify the URL
            int httpCode = http.GET();  // Make the request

            if (httpCode > 0) {  // Check for the returning code

                String payload = http.getString();
                // Serial.println(httpCode); //200 if successful

                Serial.print("Flag is: ");
                Serial.println(payload);

                if (payload == "true") {
                    previousDelayedSweepFlagtime = millis();
                    delayedSweepFlag = true;
                    Serial.println("Motor Moving to 90");
                    motor->turnMotor(400);

                    http.addHeader("Content-Type", "application/json");
                    int httpFlagResponseCode = http.PUT("false");
                    // change server flag back to false if it is true
                    http.end();  // Free the resources

                    // http.begin(
                    //     "https://automated-solar-blinds-default-rtdb.firebaseio.com/"
                    //     "optimalAngle.json");  // Specify the URL
                    // http.addHeader("Content-Type", "application/json");

                    // int optimalAngle = motor->calibrationSweep();
                    // // random number from 0 to 90
                    // int httpOptimalAngleResponseCode = http.PUT(String(optimalAngle));

                    // Serial.print("Updated server angle to ");
                    // Serial.println(optimalAngle);
                }
                http.begin(
                    "https://"
                    "automated-solar-blinds-default-rtdb.firebaseio.com/"
                    "angle.json");          // Specify the URL
                int httpCode = http.GET();  // Make the request
                if (httpCode > 0) {         // Check for the returning code
                    String newAngle = http.getString();
                    systemLogger->logVerbose(
                        tag, "The current angle is: " + (std::string)newAngle.c_str());
                    int newAngleInt = newAngle.toInt();
                    motor->turnMotor(newAngleInt * 1600 / 360);
                }
                http.end();       // Free the resources
                time = millis();  // Reset millis time
            }
        } else {
            systemLogger->logError(tag, "Error on HTTP request");
        }
    }
}

int WiFiHTTCP::write(std::string msg) {
    systemLogger->logError(tag, "Write not implemented");
    return 0;
}

int WiFiHTTCP::read() {
    systemLogger->logError(tag, "Read not implemented");
    return 0;
}

int WiFiHTTCP::available() {
    systemLogger->logError(tag, "Available not implemented");
    return 0;
}

WiFiClient *WiFiHTTCP::getTCPClient() { return TCPClient; }

void WiFiHTTCP::optimalAngleSearch(void) {}

void WiFiHTTCP::updateFlag(void) {}
