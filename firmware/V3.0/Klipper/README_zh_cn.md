# [View English version](./README.md)

# 在 SKR-mini-E3-V3.0 主板上使用 Klipper

## 注意: 

* 此主板出厂时自带了引导程序，允许通过microSD卡更新固件(firmware.bin)。

## 编译固件
1. 预编译的固件(预编译的固件源码版本是 [Commits on Mar 10, 2022](https://github.com/Klipper3d/klipper/commit/4ce2d379bb538085c960eedd5fd1dd393f497bb7))
   * [firmware-USB.bin](./firmware-USB.bin) 使用 USB 与树莓派通信。直接通过数据线将树莓派的 USB-A 连接到主板的 MicroUSB 接口即可正常通信。
   * [firmware-USART2.bin](./firmware-USART2.bin) 使用 TFT 端口的 USART2 与树莓派通信. 通过杜邦线将树莓派的 UART-TX 接到主板的 USART-RX2 ，将树莓派的 UART-RX 接到主板的 USART-TX2 ，并且将地线连接在一起即可正常通信。

2. 自行编译最新版本的固件<br/>
   ***注意: `STM32G0B1` 已经合并到 Klipper 官方 github 的 master 分支中了，所以现在我们可以完全使用 Klipper 官网的教程步骤了***
   1. 参考 [klipper官方的安装说明](https://www.klipper3d.org/Installation.html) 下载klipper源码到树莓派
   2. 使用下面的配置去编译固件 (如果您的klipper无法选择如下的配置，请更新您的klipper源码)
      * [*] Enable extra low-level configuration options
      * Micro-controller Architecture = `STMicroelectronics STM32`
      * Processor model = `STM32G0B1`
      * Bootloader offset = `8KiB bootloader (stm32duino)`
      * Clock Reference = `8 MHz crystal`
      * 如果使用 USB 与树莓派通信
         * Communication interface = `USB (on PA11/PA12)`
      * 如果使用 USART2 与树莓派通信
         * Communication interface = `Serial (on USART2 PA3/PA2)`
      * 或者
         * Communication interface = `你自己想使用的端口`

      <img src=Images/menuconfig.png width="800" /><br/>
   3. 配置选择完成后, 输入 `q` 退出配置界面，当询问是否保存配置是选择 "Yes" .
   4. 输入 `make` 命令开始编译固件
   5. 当 `make` 命令执行完成后，会在树莓派的`home/pi/kliiper/out`的文件夹中生成我们所需要的`klipper.bin`固件。你可以在CMD命令行终端中通过`pscp`命令把`klipper.bin`固件复制到与树莓派在同一个局域网下的电脑上。例如 `pscp -C pi@192.168.0.101:/home/pi/klipper/out/klipper.bin c:\klipper.bin`(命令行会提示 `The server's host key is not cached` 并且询问 `Store key in cache?((y/n)`, 输入 `y` 保存 host key，然后输入树莓派默认的密码：`raspberry`)

## 更新固件
1. 你可以使用 [编译固件 2.5](#编译固件) 中的方法或者使用 `cyberduck`、 `winscp` 工具软件从树莓派中将 `klipper.bin` 文件复制到电脑上
2. 将我们提供的`firmware-USB.bin`, `firmware-USART2.bin` 或者你自行编译的 `klipper.bin` 文件重命名为 `firmware.bin`<br/>
**提示:** 如果没有重命名为 `firmware.bin`，引导程序将不会识别并更新此文件
3. 复制 `firmware.bin` 到microSD卡的根目录中(确保SD卡的文件系统是FAT32格式)
4. 将主板断电
5. 插入microSD卡
6. 给主板通电
7. 仅需几秒钟，主板就会自动完成更新固件的步骤
8. 你可以输入 `ls /dev/serial/by-id` 查询主板的串口ID来确认固件是否烧录成功，如果烧录成功了会返回一个klipper的设备ID，如下图所示:

   <img src=Images/stm32g0b1_id.png width="600" /><br/>

   (注意: 此步骤仅适用于USB通信的工作方式，如果使用USART通信则没有这种ID)

## 配置打印机的参数
### 基础配置
1. 参考 [klipper官方的安装说明](https://www.klipper3d.org/Installation.html) to `Configuring OctoPrint to use Klipper`
2. 参考 [klipper官方的安装说明](https://www.klipper3d.org/Installation.html) to `Configuring Klipper`. 并且使用我们提供的配置文件 [SKR-mini-E3-V3.0-klipper.cfg](./SKR-mini-E3-V3.0-klipper.cfg) 为基础去修改 `printer.cfg`, 此文件中包含了主板几乎所有的pinout
3. 参考 [klipper官方的配置说明Config_Reference](https://www.klipper3d.org/Config_Reference.html) 去配置你想要的特性和功能
4. 如果你想通过USB与树莓派通信，运行 `ls /dev/serial/by-id/*` 命令去查询主板的设备ID号，在 `printer.cfg` 设置查询到的实际设备ID号
    ```
    [mcu]
    serial: /dev/serial/by-id/usb-Klipper_stm32g0b1xx_4D003C000B50345033313820-if00
    ```
5. 如果你想通过USART2与树莓派通信, 你需要修改一下的文件(你可以通过SSH终端输入命令修改，可以直接修改树莓派系统SD卡中的文件)
   * 在 `/boot/cmdline.txt` 文件中删除 `console=serial0,115200` 
   * 在 `/boot/config.txt` 文件的末尾添加 `dtoverlay=pi3-miniuart-bt`
   * 修改配置文件 `printer.cfg` 的 `[mcu]` 部分为 `serial: /dev/ttyAMA0` 并且添加 `restart_method: command`
     ```
     [mcu]
     serial: /dev/ttyAMA0
     restart_method: command
     ```
     <img src=Images/cfg_uart.png/><br/>

### BigTreeTech TFT 触摸屏模拟12864模式(Marlin 模式):  将 `printer.cfg` 的 `display` 部分设置为如下所示
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
