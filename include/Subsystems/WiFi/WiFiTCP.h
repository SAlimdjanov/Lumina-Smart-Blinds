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

#include <Subsystems/Utilities/SystemLogger.h>

#include <string>

#include "WiFi.h"

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
    std::string tag = "WiFiTCP";
    WiFiClient *TCPClient;
    bool isWiFiConnected;
    long lastTCPAttemptTimestamp;
    SystemLogger *systemLogger;
};
