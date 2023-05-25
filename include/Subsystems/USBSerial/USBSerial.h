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
    /**
     * @brief Initial USB Serial communications
     *
     */
    void initialize(void);

    /**
     * @brief Write to serial monitor
     *
     * @param message Message contents
     * @return int (length)
     */
    int write(std::string message);

    /**
     * @brief Read serial data
     *
     * @return int (length)
     */
    int read(void);

    /**
     * @brief Check if serial data is available
     *
     * @return int
     */
    int available(void);

   private:
    const int SERIAL_BAUD_RATE = 115200;
};