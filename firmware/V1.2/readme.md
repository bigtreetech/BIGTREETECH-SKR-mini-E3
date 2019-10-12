1. Install the compilation environment, We recommend vscode + platformio. If you have already installed it, please skip this step.  If not, please see [here](https://github.com/bigtreetech/Document/blob/master/How%20to%20install%20VScode+Platformio.md).
2. If you use the firmware of this repository, you just need to customize the function that you want and recompile it(Because Marlin 2.0 is in bugfix state, this repository may not be the latest version of Marlin 2.0).
3. If you want to use the latest version of Marlin 2.0, please download from the [official GitHub website of marlin](https://github.com/MarlinFirmware/Marlin/tree/bugfix-2.0.x)
4. In the lower left corner of the VSCode, you can see that there’s one more icon, please see the picture below, 
which is the PlatformIO plugin, and then click "Open Project" to open the project.![image](https://user-images.githubusercontent.com/25599056/60634053-0aee5d80-9e40-11e9-9658-7cac8b6d1002.png)
### If you are using the official Marlin 2.0 version, you need the following additional changes
* After opening the project, go to the platformio.ini file and change the default environment from megaatmega2560 to STM32F103RC_bigtree, `env_default = STM32F103RC_bigtree`
* comment out `TMCStepper@>=0.5.0,<1.0.0` add `https://github.com/bigtreetech/TMCStepper` (Because of the 'write only' function still exists in the official TMC library file, the feedback of TMC2209 cannot be read normally when RX_PIN = TX_PIN)
* comment out `Adafruit NeoPixel@1.2.5` add `https://github.com/bigtreetech/Adafruit_NeoPixel` (Because of official library files do not support smt32f1 maple Libraries)
![image](https://user-images.githubusercontent.com/25599056/66630670-4a92c580-ec37-11e9-9c40-2d9f095ce4af.png)
* add `-DHAVE_SW_SERIAL` in build_flags
![image](https://user-images.githubusercontent.com/25599056/66633694-fd662200-ec3d-11e9-9569-4c27f1123dc6.png)

* In the repo you just cloned, copy the contents of config\examples\Creality\Ender-3\ to Marlin
* Then go to the Configuration.h file and modify it:

`#define SERIAL_PORT 2`

`#define SERIAL_PORT_2 -1`

`#define BAUDRATE 115200`

`#define MOTHERBOARD BOARD_BTT_SKR_MINI_E3_V1_2`
 ![image](https://user-images.githubusercontent.com/25599056/66630522-0c95a180-ec37-11e9-9560-3c2b729b3310.png)
* modify X/Y/Z/E0 step motor driver type to `TMC2209`
![image](https://user-images.githubusercontent.com/25599056/60634508-b0560100-9e41-11e9-9a3a-2fc217564a15.png)
* this board support `CR10_STOCKDISPLAY` 
![image](https://user-images.githubusercontent.com/25599056/60634579-ff9c3180-9e41-11e9-91aa-ae90dbbbdd3f.png)
* NEED NOT modify the TMC2209 slave address, default 0 is ok!
* comment out `//#define SPEAKER`, if you don't comment out this, it will freeze when you pressed button
![image](https://user-images.githubusercontent.com/25599056/61014965-6e3a3b80-a3bc-11e9-8035-6463a2757cd7.png)
### if you enable BLTOUCH
* Please enable `#define FAN_SOFT_PWM` too, if not the fan will modify servo control signal duty cycle
 ![image](https://user-images.githubusercontent.com/25599056/66694083-95b5e280-ece2-11e9-819b-e2ae3a710a83.png)
* After the modification is complete, press Ctrl+Alt+B, and platformio will automatically download the compiled component and compile it. After the compilation is successful, a firmware.bin file will be generated in the .pio\build\STM32F103RC_bigtree directory. We will copy this file to the TF card of the motherboard, and then reset the motherboard, so that the firmware is burned into the motherboard, the red led D10 will always blink in the burning, After the burning is completed, D10 stop blink, and the file name in the TF card will change from 'firmware.bin' to 'FIRMWARE.CUR'

