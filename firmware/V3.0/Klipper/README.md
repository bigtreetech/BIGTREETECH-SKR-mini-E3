# [切换到中文版](./README_zh_cn.md)

# How to use Klipper on SKR-mini-E3-V3.0

## NOTE: 

* This motherboard comes with bootloader which allows firmware update through SD card.

## Build Firmware Image

1. Precompiled firmware(The source code version used is [Commits on Mar 10, 2022](https://github.com/Klipper3d/klipper/commit/4ce2d379bb538085c960eedd5fd1dd393f497bb7))
   * [firmware-USB.bin](./firmware-USB.bin) Use USB to communicate with raspberry pi. Connect the type-A USB of raspberry pi with the MicroUSB of motherboard directly to communicate normally.
   * [firmware-USART2.bin](./firmware-USART2.bin) Use TFT port USART2 to communicate with raspberry pi. Connect the UART-TX of raspberry pi with the USART-RX2 of motherboard and connect the UART-RX of raspberry pi with the USART-TX2 of motherboard directly to communicate normally.

2. Build your own firmware<br/>
   ***NOTE: `STM32G0B1` has now been merged into the master branch of klipper's official github repository, so now we can use the steps on the klipper official website***
   1. Refer to [klipper's official installation](https://www.klipper3d.org/Installation.html) to download klipper source code to raspberry pi.
   2. `Building the micro-controller` with the configuration shown below. (If your klipper cannot select the following configuration, please update your klipper source code)
      * [*] Enable extra low-level configuration options
      * Micro-controller Architecture = `STMicroelectronics STM32`
      * Processor model = `STM32G0B1`
      * Bootloader offset = `8KiB bootloader (stm32duino)`
      * Clock Reference = `8 MHz crystal`
      * IF USE USB
         * Communication interface = `USB (on PA11/PA12)`
      * ElSE IF USE USART2
         * Communication interface = `Serial (on USART2 PA3/PA2)`
      * ELSE
         * Communication interface = `The port you want`

      <img src=Images/menuconfig.png width="800" /><br/>
   3. Once the configuration is selected, press `q` to exit,  and "Yes" when  asked to save the configuration.
   4. Run the command `make`
   5. The `klipper.bin` file will be generated in the folder `home/pi/kliiper/out` when the `make` command completed. And you can use the windows computer under the same LAN as raspberry pi to copy `klipper.bin` from raspberry pi to the computer with `pscp` command in the CMD terminal. such as `pscp -C pi@192.168.0.101:/home/pi/klipper/out/klipper.bin c:\klipper.bin`(The terminal may prompt that `The server's host key is not cached` and ask `Store key in cache?((y/n)`, Please type `y` to store. And then it will ask for a password, please type the default password `raspberry` for raspberry pi)

## Firmware Installation
1. You can use the method in [Build Firmware Image 2.5](#build-firmware-image) or use a tool such as `cyberduck` or `winscp` to copy the `klipper.bin` file from your pi to your computer.
2. Renamed the `firmware-USB.bin`, `firmware-USART2.bin` or the `klipper.bin`(in folder `home/pi/kliiper/out` build by yourself) to `firmware.bin`<br/>
**Important:** If the file is not renamed, the bootloader will not be updated properly.
3. Copy the `firmware.bin` to the root directory of SD card (make sure SD card is in FAT32 format)
4. power off the SKR-mini-E3-V3.0
5. insert the microSD card
6. power on the SKR-mini-E3-V3.0
7. after a few seconds, the SKR-mini-E3-V3.0 should be flashed
8. you can confirm that the flash was successful, by running `ls /dev/serial/by-id`.  if the flash was successful, this should now show a klipper device, similar to:

   <img src=Images/stm32g0b1_id.png width="600" /><br/>

   (note: this test is not appicable if the firmware was compiled for UART, rather than USB)

## Configure the printer parameters
### Basic configuration
1. Refer to [klipper's official installation](https://www.klipper3d.org/Installation.html) to `Configuring OctoPrint to use Klipper`
2. Refer to [klipper's official installation](https://www.klipper3d.org/Installation.html) to `Configuring Klipper`. And use the configuration file [SKR-mini-E3-V3.0-klipper.cfg](./SKR-mini-E3-V3.0-klipper.cfg) as the underlying `printer.cfg`, which includes all the correct pinout for Octopus
3. Refer to [klipper's official Config_Reference](https://www.klipper3d.org/Config_Reference.html) to configure the features you want.
4. If you use USB to communicate with raspberry pi, run the `ls /dev/serial/by-id/*` command in raspberry pi to get the correct ID number of the motherboard, and set the correct ID number in `printer.cfg`.
    ```
    [mcu]
    serial: /dev/serial/by-id/usb-Klipper_stm32g0b1xx_4D003C000B50345033313820-if00
    ```
5. If you use USART2 to communicate with raspberry pi, you need to modify the following files by inserting the SD card into the computer or by SSH command.
   * Remove `console=serial0,115200` in `/boot/cmdline.txt`
   * Add `dtoverlay=pi3-miniuart-bt` at the end of file `/boot/config.txt`
   * Modify the configuration of `[mcu]` in `printer.cfg` to `serial: /dev/ttyAMA0` and enable `restart_method: command` by SSH
     ```
     [mcu]
     serial: /dev/ttyAMA0
     restart_method: command
     ```
     <img src=Images/cfg_uart.png/><br/>

### BigTreeTech TFT TouchScreen emulated 12864 mode: Set the `display` in `printer.cfg` to the following parameters
   ```
   [display]
   lcd_type: emulated_st7920
   spi_software_miso_pin: PD8 # status led, Virtual MISO
   spi_software_mosi_pin: PD6
   spi_software_sclk_pin: PB9
   en_pin: PB8
   encoder_pins: ^PA10, ^PA9
   click_pin: ^!PA15

   [output_pin beeper]
   pin: PB5
   ```
   <img src=Images/cfg_tft_emulated_12864.png/><br/>
