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

#include <AccelStepper.h>
#include <Arduino.h>
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
    void turnMotor(int steps);

    /**
     * @brief Rotate the stepper motor clockwise
     *
     * @param steps Number of steps to travel
     *
     */
    void turnCW(int steps);

    /**
     * @brief Stop Stepper Motor
     *
     */
    void stopMotor(void);

    /**
     * @brief Run stepper in infinite loop
     *
     */
    void runStepper(void);

    /**
     * @brief Rotate from 0-90 deg. positions to measure optimal angle
     *
     * @return maximum measured digital voltage value (int)
     *
     */
    int calibrationSweep(void);

    /**
     * @brief Check if motor is still in motion via position comparison
     *
     * @return true
     * @return false
     */
    bool inMotion(void);

    /**
     * @brief Check if limit switch activated
     *
     * @return true
     * @return false
     */
    bool isAtNinetyDegrees(void);

   private:
    // Module tag string
    std::string tag = "Stepper Motor";
    // Motor speed (RPM)
    const int MOTOR_SPEED = 1;
    // Obtain instance of logger
    SystemLogger* systemLogger = SystemLogger::getLogger();
    int voltageValues[90];
    long remainingSteps = 0;
    long currentPosition = 0;
};
