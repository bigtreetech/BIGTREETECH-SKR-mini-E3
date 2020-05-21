/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once


#define BOARD_INFO_NAME "BIGTREE SKR Mini E3 V2.0"

// Release PA13/PA14 (led, usb control) from SWD pins
#define DISABLE_DEBUG

#define I2C_EEPROM  // On board AT24C32
#define E2END       (0xFFF) // 4KB

#define NEOPIXEL_PIN                       PA8   // LED driving pin

#define USB_CONNECT_PIN                    PA14  // USB connect control

#define PS_ON_PIN                          PC13  // Power Supply Control

#define FAN_PIN                            PC6
#define FAN1_PIN                           PC7
#ifndef CONTROLLER_FAN_PIN
  #define CONTROLLER_FAN_PIN               FAN1_PIN
#endif
/**
 * TMC220x stepper drivers
 * Hardware serial communication ports.
 */
#if HAS_TMC_UART
  #define X_HARDWARE_SERIAL  Serial4
  #define Y_HARDWARE_SERIAL  Serial4
  #define Z_HARDWARE_SERIAL  Serial4
  #define E0_HARDWARE_SERIAL Serial4
#endif


/**
 *                 _____
 *             5V | 1 2 | GND
 *  (LCD_EN) PB15 | 3 4 | PB8  (LCD_RS)
 *  (LCD_D4) PB9  | 5 6   PA10 (BTN_EN2)
 *          RESET | 7 8 | PA9  (BTN_EN1)
 * (BTN_ENC) PA15 | 9 10| PB5  (BEEPER)
 *                 -----
 *                 EXP1
 */

#define EXPA1_03_PIN                        PB15
#define EXPA1_09_PIN                        PA15

#include "pins_BTT_SKR_MINI_E3.h"