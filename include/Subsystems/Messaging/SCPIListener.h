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
    /**
     * @brief Construct a new SCPIListener object
     *
     */
    SCPIListener();

    /**
     * @brief Listen for SCPI command
     *
     */
    void listenForCommand();

    /**
     * @brief Register an incoming command
     *
     * @param command Flash string input
     * @param caller SCPI caller object
     */
    void registerNewMessage(const __FlashStringHelper *command,
                            SCPI_caller_t caller);

    /**
     * @brief Add new communication interface
     *
     * @param interface Communication module
     */
    void addNewInterface(Stream *interface);

   private:
    // SCPI Listener module tag
    std::string tag = "SCPI Listener";
    // SCPI Parser object
    SCPI_Parser scpiParser;
    // Obtain instance of logger
    SystemLogger *systemLogger = SystemLogger::getLogger();
    // Interface vector container
    std::vector<Stream *> interfaceList;
};