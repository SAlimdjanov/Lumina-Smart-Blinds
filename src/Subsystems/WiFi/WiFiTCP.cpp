#include <Subsystems/WiFi/WiFiTCP.h>

const char *NETWORK_ID = "Name";
const char *PASSWORD = "Password";

const uint16_t PORT_ID = 10000;
const char *HOST_IP = "192.000.000.000";

const long TCP_CONNECT_TIME_INTERVAL = 1000;

WiFiTCP::WiFiTCP()
    : TCPClient(new WiFiClient()),
      isWiFiConnected(false),
      lastTCPAttemptTimestamp(0),
      systemLogger(SystemLogger::getLogger()) {}

void WiFiTCP::initialize() {
    WiFi.begin(NETWORK_ID, PASSWORD);
    systemLogger->logInfo(tag, "Connecting to Wi-Fi");
}

void WiFiTCP::checkConnection() {
    if (!isWiFiConnected) {
        if (WiFi.status() == WL_CONNECTED) {
            isWiFiConnected = true;
            systemLogger->logInfo(tag, "Wi-Fi connection established");
        }
        return;
    }
    if (WiFi.status() != WL_CONNECTED) {
        systemLogger->logInfo(
            tag, "Wi-Fi connection lost. Attempting to reconnect.");
        WiFi.disconnect();
        isWiFiConnected = false;
        WiFi.begin(NETWORK_ID, PASSWORD);
        return;
    }
    if (!TCPClient->connected()) {
        if ((millis() - this->lastTCPAttemptTimestamp) >=
            TCP_CONNECT_TIME_INTERVAL) {
            systemLogger->logInfo(tag, "Attempting connect to TCP");
            if (TCPClient->connect(HOST_IP, PORT_ID, 10)) {
                systemLogger->logInfo(tag, "TCP connection established.");
            }
            this->lastTCPAttemptTimestamp = millis();
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