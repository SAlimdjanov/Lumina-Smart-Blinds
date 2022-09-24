/**
 * @file SolarBlinds.h
 * @author Sean Alimdjanov (alimdjas@mcmaster.ca)
 * @brief Solar Blinds Master Class
 * @version 0.1
 * @date 2022-09-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <Subsystems/SCPIHandler.h>
#include <Subsystems/SerialUSB/USBSerial.h>
#include <Subsystems/StepperMotor/StepperMotor.h>

class SolarBlinds {
   public:
    /**
     * @brief Initialize Solar Blinds
     *
     */
    void initialize(void);

    /**
     * @brief Run Solar Blind Software
     *
     */
    void run(void);

   private:
    StepMotor *stepMotor;  // Step Motor Class Object
    USBSerial *usbSerial;  // USB Serial Class Object
};