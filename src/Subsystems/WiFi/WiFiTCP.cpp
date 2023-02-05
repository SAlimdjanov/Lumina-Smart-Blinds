#include <Subsystems/WiFi/WiFiTCP.h>

const char *SSID = "networkname";
const char *PASSWORD = "password";

int currentAngle = 0;

StepMotor *WiFiTCP::motor = new StepMotor();

WiFiTCP::WiFiTCP()
    : TCPClient(new WiFiClient()),
      isWiFiConnected(false),
      lastTCPAttemptTimestamp(0),
      systemLogger(SystemLogger::getLogger()) {}

void WiFiTCP::initialize() {
    WiFi.mode(WIFI_STA);  // Optional
    WiFi.begin(SSID, PASSWORD);
    Serial.println("\nConnecting");

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to Blinds!\n");

    time = millis() + 1000;  // Delay first get request to avoid init error
}

void WiFiTCP::checkConnection() {  // Rename? (Functionality may change)
    if (millis() - time >= POLLING_INTERVAL) {
        if ((WiFi.status() ==
             WL_CONNECTED)) {  // Check the current connection status
            HTTPClient http;

            http.begin(
                "https://automated-solar-blinds-default-rtdb.firebaseio.com/"
                "angle.json");          // Specify the URL
            int httpCode = http.GET();  // Make the request

            if (httpCode > 0) {  // Check for the returning code
                String newAngle = http.getString();
                Serial.print("The current angle is: ");
                Serial.println(newAngle);
                int newAngleInt = newAngle.toInt();
                if (newAngleInt > currentAngle) {
                    motor->turnCW(
                        round((newAngleInt - currentAngle) * 2048 / 360));
                } else if (newAngleInt < currentAngle) {
                    motor->turnCCW(
                        round((currentAngle - newAngleInt) * 2048 / 360));
                }
                currentAngle = newAngleInt;
            }

            else {
                Serial.println("Error on HTTP request");
            }

            http.end();       // Free the resources
            time = millis();  // Reset millis time
        }
    }
}

int WiFiTCP::write(std::string msg) {
    systemLogger->logError(tag, "Write not implemented");
    return 0;
}

int WiFiTCP::read() {
    systemLogger->logError(tag, "Read not implemented");
    return 0;
}

int WiFiTCP::available() {
    systemLogger->logError(tag, "Available not implemented");
    return 0;
}

WiFiClient *WiFiTCP::getTCPClient() { return TCPClient; }