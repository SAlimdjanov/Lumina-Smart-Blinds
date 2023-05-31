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
     * @brief Rotate from 0-90 deg. positions to allow voltage measurements
     *
     *
     */
    void calibrationSweep(void);

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

    /**
     * @brief Measure voltage value
     *
     */
    void measureVoltage(void);

    /**
     * @brief Re-enable stepper
     *
     */
    void reenableMotor(void);

   private:
    // Module Tag
    std::string tag = "Stepper Motor";
    // Motor Speed (RPM)
    const int MOTOR_SPEED = 1;
    // Logger Object
    SystemLogger* systemLogger = SystemLogger::getLogger();
    // Measured Voltage value array
    int voltageValues[90];
    // Remaining motor steps
    long remainingSteps = 0;
    // Current motor position
    long currentPosition = 0;
    // Motor sweep angle
    int sweepAngle = 90;
};
