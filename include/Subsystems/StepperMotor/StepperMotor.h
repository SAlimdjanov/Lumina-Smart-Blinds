/**
 * @file StepperMotor.h
 * @author Sean Alimdjanov (alimdjas@mcmaster.ca)
 * @brief Stepper motor implementation
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
    /**
     * @brief Construct a new Step Motor object
     *
     */
    StepMotor();
    /**
     * @brief Initialize stepper motor
     *
     */
    void initialize(void);

    /**
     * @brief Rotate the stepper motor counterclockwise
     *
     * @param steps Number of steps to travel
     *
     */
    void turnCCW(int steps);

    /**
     * @brief Rotate the stepper motor clockwise
     *
     * @param steps Number of steps to travel
     *
     */
    void turnCW(int steps);

    /**
     * @brief Stop motor
     *
     */
    void stop(void);

   private:
    // Module tag string
    std::string tag = "Stepper Motor";
    // Motor speed (RPM)
    const int MOTOR_SPEED = 10;
    // Obtain instance of logger
    SystemLogger* systemLogger = SystemLogger::getLogger();
};
