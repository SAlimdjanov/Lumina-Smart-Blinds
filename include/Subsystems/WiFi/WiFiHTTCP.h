/**
 * @file WiFiHTTCP.h
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

class WiFiHTTCP {
   public:
    /**
     * @brief Construct a new WiFiHTTCP object
     *
     */
    WiFiHTTCP();

    /**
     * @brief Initialize module
     *
     */
    void initialize();

    /**
     * @brief Check connection to Wi-Fi and initiate motor movements accordingly
     *
     */
    void checkConnection();

    /**
     * @brief Get TCPClient object
     *
     * @return WiFiClient*
     */
    WiFiClient *getTCPClient();

   private:
    // Time tracking variable
    unsigned long time;
    // Polling time (ms)
    int POLLING_INTERVAL = 1000;
    // Module Tag
    std::string tag = "WiFiHTTCP";
    // TCPClient Object
    WiFiClient *TCPClient;
    // WiFi connection flag
    bool isWiFiConnected;
    // Last TCP attempt time
    long lastTCPAttemptTimestamp;
    // Logger Object
    SystemLogger *systemLogger;
    // Stepper Motor object
    static StepMotor *motor;
    // Measured voltage
    int maxMeasuredVoltage;
    // Motor movement flag
    bool isMotorMoving;
};
