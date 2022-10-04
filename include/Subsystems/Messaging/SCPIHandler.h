/**
 * @file SCPIHandler.h
 * @author Sean Alimdjanov (alimdjas@mcmaster.ca)
 * @brief SCPI Handler Class
 * @version 0.1
 * @date 2022-09-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <Arduino.h>
#include <Subsystems/Messaging/SCPIListener.h>
#include <Subsystems/StepperMotor/StepperMotor.h>
#include <Subsystems/Utilities/SystemLogger.h>
#include <Vrekrer_scpi_parser.h>
#include <WString.h>


class SCPIHandler {
   public:
    /**
     * @brief Construct a new SCPIHandler object
     *
     * @param listener SCPI listener object
     */
    SCPIHandler(SCPIListener *listener);

    /**
     * @brief Returns project name
     *
     * @param messages Command "*IDN?"
     * @param parameters SCPI Parameters (none)
     * @param interface Corresponding interface
     */
    static void identifyCommand(SCPI_C messages, SCPI_P parameters,
                                Stream &interface);

    /**
     * @brief Stops Motor
     *
     * @param messages Command "MOTOr:STOP"
     * @param parameters SCPI Parameters (none)
     * @param interface Corresponding interface
     */
    static void stopMotor(SCPI_C messages, SCPI_P parameters,
                          Stream &interface);

    /**
     * @brief Turn the motor clockwise
     *
     * @param messages Command "MOTOr:MCW"
     * @param parameters SCPI Parameters (steps, direction)
     * @param interface Corresponding interface
     */
    static void moveMotorClockwise(SCPI_C messages, SCPI_P parameters,
                                   Stream &interface);

    /**
     * @brief Turn the motor counterclockwise
     *
     * @param messages Command "MOTOr:MCCW"
     * @param parameters SCPI Parameters (steps, direction)
     * @param interface Corresponding interface
     */
    static void moveMotorCounterclockwise(SCPI_C messages, SCPI_P parameters,
                                          Stream &interface);

   private:
    // SCPI Handler module tag
    static std::string tag;
    // SCPI Listener object
    SCPIListener *scpiListener;
    // System Logger object
    static SystemLogger *systemLogger;
    // Stepper Motor Object
    static StepMotor *stepperMotor;

    /**
     * @brief Check if SCPI parameter input is valid
     *
     * @param parameters Input parameters
     * @param expectedNumber Expected number of parameters
     * @param interface Corresponding interface
     * @return true
     * @return false
     */
    static bool areParametersValid(SCPI_P parameters, int expectedNumber,
                                   Stream &interface);
};