1. Install the compilation environment, We recommend vscode + platformio. If you have already installed it, please skip this step.  If not, please see [here](https://github.com/bigtreetech/Document/blob/master/How%20to%20install%20VScode+Platformio.md).
2. Download the latest Marlin 2.0 firmware from the [official GitHub website of marlin](https://github.com/MarlinFirmware/Marlin/tree/bugfix-2.0.x)
3. Compile Marlin
* In the lower left corner of the VSCode, you can see that there’s one more icon, please see the picture below, 
which is the PlatformIO plugin, and then click "Open Project" to open the project.![image](https://user-images.githubusercontent.com/25599056/60634053-0aee5d80-9e40-11e9-9658-7cac8b6d1002.png)
* After opening the project, go to the platformio.ini file and change the default environment from megaatmega2560 to BIGTREE_SKR_MINI, `env_default = BIGTREE_SKR_MINI`![image](https://user-images.githubusercontent.com/25599056/60634202-bac3cb00-9e40-11e9-9d66-089c2b925138.png)
* In the repo you just cloned, copy the contents of config\examples\Creality\Ender-3\ to Marlin
* Then go to the Configuration.h file and modify it:

`#define SERIAL_PORT 2`

`#define SERIAL_PORT_2 -1`

`#define BAUDRATE 115200`

`#define MOTHERBOARD BOARD_BIGTREE_SKR_MINI_E3`
![image](https://user-images.githubusercontent.com/25599056/60634464-8ac8f780-9e41-11e9-9644-f2462160818a.png)
* modify X/Y/Z/E0 step motor driver type to `TMC2209`
![image](https://user-images.githubusercontent.com/25599056/60634508-b0560100-9e41-11e9-9a3a-2fc217564a15.png)
* this board support `CR10_STOCKDISPLAY` 
![image](https://user-images.githubusercontent.com/25599056/60634579-ff9c3180-9e41-11e9-91aa-ae90dbbbdd3f.png)
* go to the Configuration_adv.h file and modify the TMC2209 slave address

`#define  X_SLAVE_ADDRESS 0`

`#define  Y_SLAVE_ADDRESS 2`
  
`#define  Z_SLAVE_ADDRESS 1`

`#define E0_SLAVE_ADDRESS 3`
![image](https://user-images.githubusercontent.com/25599056/64931060-9173e200-d868-11e9-8811-6b86eea15f4d.png)
* comment out `//#define EEPROM_SETTINGS`
![image](https://user-images.githubusercontent.com/25599056/61014947-5f538900-a3bc-11e9-8017-2bcf9bc18411.png)
* comment out `//#define SPEAKER`, if you don't comment out this, it will freeze when you pressed button
![image](https://user-images.githubusercontent.com/25599056/61014965-6e3a3b80-a3bc-11e9-8035-6463a2757cd7.png)
* if you enable BLTOUCH, please enable `#define ENDSTOP_INTERRUPTS_FEATURE` too, this is because of that the feedback signal of bltouch   is a short pulse rather than a continuous high level, Interruption is required to ensure that 100% of the signal is captured.
![image](https://user-images.githubusercontent.com/25599056/63660618-bfc24c80-c7e9-11e9-9d81-6b8ce55b1f07.png)
* After the modification is complete, press Ctrl+Alt+B, and platformio will automatically download the compiled component and compile it. After the compilation is successful, a firmware.bin file will be generated in the .pio\build\BIGTREE_SKR_MINI directory. We will copy this file to the TF card of the motherboard, and then reset the motherboard, so that the firmware is burned into the motherboard, the red led D10 will always blink in the burning, After the burning is completed, D10 stop blink, and the file name in the TF card will change from 'firmware.bin' to 'FIRMWARE.CUR'

