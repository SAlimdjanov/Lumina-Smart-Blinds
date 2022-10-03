/**
 * @file StepperMotor.h
 * @author Sean Alimdjanov (alimdjas@mcmaster.ca)
 * @brief
 * @version 0.1
 * @date 2022-09-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <Arduino.h>
#include <Stepper.h>
#include <Subsystems/Utilities/SystemLogger.h>
#include <esp32-hal-gpio.h>

class StepMotor {
   public:
    StepMotor();
    /**
     * @brief Initialize stepper motor
     *
     */
    void initialize(void);

    /**
     * @brief Rotate the stepper motor
     *
     * @param steps Number of steps to travel
     * @param direction direction of rotation
     *
     */
    void turn(int steps, int direction);

   private:
    std::string tag = "Stepper Motor";
    SystemLogger* systemLogger = SystemLogger::getLogger();
};
