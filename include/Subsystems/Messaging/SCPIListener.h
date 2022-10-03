/**
 * @file SCPIListener.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-09-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <Arduino.h>
#include <Subsystems/Utilities/SystemLogger.h>
#include <Vrekrer_scpi_parser.h>

class SCPIListener {
   public:
    SCPIListener();
    void listenForCommand();
    void registerNewMessage(const __FlashStringHelper *command,
                            SCPI_caller_t caller);
    void addNewInterface(Stream *interface);

   private:
    std::string tag = "SCPI Listener";
    SCPI_Parser scpiParser;
    SystemLogger *systemLogger = SystemLogger::getLogger();
    std::vector<Stream *> interfaceList;
};