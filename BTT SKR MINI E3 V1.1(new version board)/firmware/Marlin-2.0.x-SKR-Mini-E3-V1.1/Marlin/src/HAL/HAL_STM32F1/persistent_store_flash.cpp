/**
 * Marlin 3D Printer Firmware
 *
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 * Copyright (c) 2016 Bob Cousins bobcousins42@googlemail.com
 * Copyright (c) 2015-2016 Nico Tonnhofer wurstnase.reprap@gmail.com
 * Copyright (c) 2016 Victor Perez victor_pv@hotmail.com
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

/**
 * persistent_store_flash.cpp
 * HAL for stm32duino and compatible (STM32F1)
 * Implementation of EEPROM settings in flash
 */

#ifdef __STM32F1__

#include "../../inc/MarlinConfig.h"

// This is for EEPROM emulation in flash
#if BOTH(EEPROM_SETTINGS, FLASH_EEPROM_EMULATION)

#include "../shared/persistent_store_api.h"
#include <flash_stm32.h>

// Store settings in EEPROM_START_ADDRESS
// Flash pages must be erased before writing, so keep track.
#define EEPROM_SIZE (E2END+1)
#define FLASH_BLANK_DATA (0xFF)

static uint8_t ram_eeprom[EEPROM_SIZE] __attribute__((aligned(4))) = {0};
static bool eeprom_update = false;
static bool flash_blank = true;

bool eeprom_flash_erase_all(void) {
  FLASH_Status status;

  for(uint32_t i = EEPROM_START_ADDRESS; i < EEPROM_START_ADDRESS + EEPROM_SIZE; i += EEPROM_PAGE_SIZE) {
    status = FLASH_ErasePage(i);
    if (status != FLASH_COMPLETE) return false;
  }
  return true;
}

bool PersistentStore::access_start() {
  uint8_t *flash_addr = (uint8_t *)EEPROM_START_ADDRESS;
  flash_blank = true;

  for (uint32_t i = 0; i < EEPROM_SIZE; i++) {
    ram_eeprom[i] = flash_addr[i];  //read EEPROM data
    if(flash_addr[i] != FLASH_BLANK_DATA) flash_blank = false;  //flash not blank
  }

  eeprom_update = false;

  return true;
}

bool PersistentStore::access_finish() {
  FLASH_Status status;

  if(!eeprom_update) return true;
  FLASH_Unlock();
  if (!flash_blank) {  //if flash not blank, flash must be erased before writing
    if(eeprom_flash_erase_all() == false) return false;
  }

  for(uint32_t i = 0; i < EEPROM_SIZE; i += 2) {
    uint16_t data16 = ram_eeprom[i] | ((i+1 < EEPROM_SIZE ? ram_eeprom[i+1] : FLASH_BLANK_DATA) << 8);  //stm32f10x needs to write at least 16 bits at a time
    status = FLASH_ProgramHalfWord(EEPROM_START_ADDRESS + i, data16);
    if (status != FLASH_COMPLETE) return false;
  }
  FLASH_Lock();
  eeprom_update = false;

  return true;
}

bool PersistentStore::write_data(int &pos, const uint8_t *value, size_t size, uint16_t *crc) {
  for (size_t i = 0; i < size; i++) ram_eeprom[pos + i] = value[i];
  eeprom_update = true;
  crc16(crc, value, size);
  pos += size;
  return false;  // return true for any error
}

bool PersistentStore::read_data(int &pos, uint8_t* value, size_t size, uint16_t *crc, const bool writing/*=true*/) {
  const uint8_t * const buff = writing ? &value[0] : &ram_eeprom[pos];
  if (writing) for (size_t i = 0; i < size; i++) value[i] = ram_eeprom[pos + i];
  crc16(crc, buff, size);
  pos += size;
  return false;  // return true for any error
}

size_t PersistentStore::capacity() { return E2END + 1; }

#endif // EEPROM_SETTINGS && EEPROM FLASH
#endif // __STM32F1__
