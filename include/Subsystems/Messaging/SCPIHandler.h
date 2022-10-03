/**
 * @file SCPIHandler.h
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
#include <Subsystems/Messaging/SCPIListener.h>
#include <Subsystems/Utilities/SystemLogger.h>
#include <Vrekrer_scpi_parser.h>
#include <WString.h>

#include "Subsystems/StepperMotor/StepperMotor.h"

class SCPIHandler {
   public:
    SCPIHandler(SCPIListener *listener);
    static void identifyCommand(SCPI_C messages, SCPI_P parameters,
                                Stream &interface);
    static void stopMotor(SCPI_C messages, SCPI_P parameters,
                          Stream &interface);
    static void moveMotorClockwise(SCPI_C messages, SCPI_P parameters,
                                   Stream &interface);
    static void moveMotorCounterclockwise(SCPI_C messages, SCPI_P parameters,
                                          Stream &interface);

   private:
    static std::string tag;
    SCPIListener *scpiListener;
    static SystemLogger *systemLogger;
    static StepMotor *stepperMotor;
    void setStepMotor(StepMotor *stepMotor);
    static bool areParametersValid(SCPI_P parameters, int expectedNumber,
                                   Stream &interface);
};