/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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

#ifndef TARGET_STM32F1
  #error "Oops! Select an STM32F1 board in 'Tools > Board.'"
#endif

#if HAS_SPI_LCD && !ENABLED(CR10_STOCKDISPLAY)
  #error "Only CR10_STOCKDISPLAY is currently supported on the BTT_SKR_MINI_E3_V1.1."
#else
  #include "pins_BIGTREE_SKR_MINI_E3.h"
#endif // LCD type error

#undef BOARD_NAME
#define BOARD_NAME "BTT SKR Mini E3 V1.1"

// Ignore temp readings during development.
//#define BOGUS_TEMPERATURE_GRACE_PERIOD 2000

#if HAS_DRIVER(TMC2209)
  #undef X_HARDWARE_SERIAL
  #undef Y_HARDWARE_SERIAL
  #undef Z_HARDWARE_SERIAL
  #undef E0_HARDWARE_SERIAL
#endif

#if HAS_TMC220x
  /**
   * TMC2208/TMC2209 stepper drivers
   * Software serial
   */

  #define X_SERIAL_TX_PIN  PB15
  #define X_SERIAL_RX_PIN  PB15

  #define Y_SERIAL_TX_PIN  PC6
  #define Y_SERIAL_RX_PIN  PC6

  #define Z_SERIAL_TX_PIN  PC10
  #define Z_SERIAL_RX_PIN  PC10

  #define E0_SERIAL_TX_PIN PC11
  #define E0_SERIAL_RX_PIN PC11
#endif

//flash emulation eeprom
#define FLASH_EEPROM_EMULATION
#define EEPROM_PAGE_SIZE	(uint16_t)0x800  /* Page size = 2KByte */
#define EEPROM_START_ADDRESS	((uint32_t)(0x8000000 + 512 * 1024 - 2 * EEPROM_PAGE_SIZE))
#define E2END 0xFFF // 4KB
