1. Install the compilation environment, We recommend vscode + platformio. If you have already installed it, please skip this step.  If not, please see [here](https://github.com/bigtreetech/Document/blob/master/How%20to%20install%20VScode+Platformio.md).
2. If you use the firmware of this repository, you just need to customize the function that you want and recompile it(Because Marlin 2.0 is in bugfix state, this repository may not be the latest version of Marlin 2.0).
3. If you want to use the latest version of Marlin 2.0, please download from the [official GitHub website of marlin](https://github.com/MarlinFirmware/Marlin/tree/bugfix-2.0.x)
4. In the lower left corner of the VSCode, you can see that there’s one more icon, please see the picture below, 
which is the PlatformIO plugin, and then click "Open Project" to open the project.![image](https://user-images.githubusercontent.com/25599056/60634053-0aee5d80-9e40-11e9-9658-7cac8b6d1002.png)
### If you are using the official Marlin 2.0 version, you need the following additional changes
* After opening the project, go to the platformio.ini file and change the default environment from megaatmega2560 to STM32F103RC_bigtree_NOUSB, `env_default = STM32F103RC_bigtree_NOUSB`

 ![image](https://user-images.githubusercontent.com/38851044/69534016-f4de6680-0fb3-11ea-972f-5daae3643061.png)

* In the repo you just cloned, copy the contents of `\config\examples\BigTreeTech\SKR Mini E3 1.0` to Marlin

 ![image](https://user-images.githubusercontent.com/38851044/69534940-c1044080-0fb5-11ea-8dcd-d29ec98e3f14.png)
 ![image](https://user-images.githubusercontent.com/38851044/69534316-7e8e3400-0fb4-11ea-8383-296760660e62.png)

* Then you can use it normally

### if you enable BLTOUCH
* enable BLTOUCH

 ![image](https://user-images.githubusercontent.com/38851044/69534485-e6447f00-0fb4-11ea-93db-db47d24cde5a.png)
 
* modify bltouch offset from nozzle

 ![image](https://user-images.githubusercontent.com/38851044/69534563-07a56b00-0fb5-11ea-9c2e-008af3f2f5d0.png)
 
* modify grid points

 ![image](https://user-images.githubusercontent.com/38851044/69534607-1b50d180-0fb5-11ea-9d14-c2f15e2b95fe.png)
 
* if you want use bltouch for z-homing, please enable `Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN`

 ![image](https://user-images.githubusercontent.com/38851044/69534698-4804e900-0fb5-11ea-9936-26fc5f8202c1.png)
 
  else, please comment out `Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN`
  
  ![image](https://user-images.githubusercontent.com/38851044/69534808-7c78a500-0fb5-11ea-9991-3234b26ccf70.png)
  
 
* After the modification is complete, press Ctrl+Alt+B, and platformio will automatically download the compiled component and compile it. After the compilation is successful, a firmware.bin file will be generated in the .pio\build\STM32F103RC_bigtree directory. We will copy this file to the TF card of the motherboard, and then reset the motherboard, so that the firmware is burned into the motherboard, the red led D10 will always blink in the burning, After the burning is completed, D10 stop blink, and the file name in the TF card will change from 'firmware.bin' to 'FIRMWARE.CUR'

