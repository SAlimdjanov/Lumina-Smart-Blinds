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

void WiFiHTTCP::checkConnection() {
    isMotorMoving = motor->inMotion();  // Rename? (Functionality may change)
    if (millis() - time >= POLLING_INTERVAL && !isMotorMoving) {
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
                    http.addHeader("Content-Type", "application/json");
                    int httpFlagResponseCode = http.PUT("false");
                    // change server flag back to false if it is true
                    http.end();  // Free the resources

                    http.begin(
                        "https://automated-solar-blinds-default-rtdb.firebaseio.com/"
                        "optimalAngle.json");  // Specify the URL
                    http.addHeader("Content-Type", "application/json");

                    int optimalAngle = motor->calibrationSweep();
                    // random number from 0 to 90
                    int httpOptimalAngleResponseCode = http.PUT(String(optimalAngle));

                    


                    Serial.print("Updated server angle to ");
                    Serial.println(optimalAngle);
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
