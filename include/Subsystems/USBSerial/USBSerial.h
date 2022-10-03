/**
 * @file USBSerial.h
 * @author Sean Alimdjanov (alimdjas@mcmaster.ca)
 * @brief USB-Serial Interface for communication with PC
 * @version 0.1
 * @date 2022-09-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <Arduino.h>

class USBSerial {
   public:
    void initialize(void);
    int write(std::string message);
    int read(void);
    int available(void);

   private:
    const int SERIAL_BAUD_RATE = 115200;
};