/**
 * @file WiFiTCP.h
 * @author Sean Alimdjanov (alimdjas@mcmaster.ca)
 * @brief WiFi Interface for Solar Blind Controller
 * @version 0.1
 * @date 2022-11-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <HTTPClient.h>
#include <Subsystems/StepperMotor/StepperMotor.h>
#include <Subsystems/Utilities/SystemLogger.h>
#include <WiFi.h>

#include <string>

class WiFiTCP {
   public:
    /**
     * @brief Construct a new WiFiTCP object
     *
     */
    WiFiTCP();
    void initialize();
    int write(std::string msg);
    int read();
    int available();
    void checkConnection();
    WiFiClient *getTCPClient();

   private:
    unsigned long time;
    int POLLING_INTERVAL = 1000;
    std::string tag = "WiFiTCP";
    WiFiClient *TCPClient;
    bool isWiFiConnected;
    long lastTCPAttemptTimestamp;
    SystemLogger *systemLogger;
    static StepMotor *motor;
};
