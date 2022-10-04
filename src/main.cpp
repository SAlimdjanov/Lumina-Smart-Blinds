/**
 * @file main.cpp
 * @author Sean Alimdjanov (alimdjas@mcmaster.ca)
 * @brief ENGPHYS 4A06 Capstone Project: Automated Solar Blinds
 * @version 0.1
 * @date 2022-09-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <Arduino.h>
#include <SolarBlinds.h>

SolarBlinds *solarBlinds = new SolarBlinds();

void setup() { solarBlinds->initialize(); }

void loop() { solarBlinds->run(); }