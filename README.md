# cdfr2020BaseRoulanteRework

Code for the robotronik club participation to the french robotics cup (WIP).
This code will implement motor control and positioning awareness by odometry.

Reminder: To clone the submodule in the same time, use `git clone --recurse-submodules`, then don't forget to build libopencm3. You need to execute `make install_udev` one time to add the permission to flash.
If you forgot to clone with submodule just run `git submodule update --init --recursive`

To compile and flash you need gcc-arm-none-eabi-bin, st-linkand  openocd

To build: `mainTest.elf`
To flash: `mainTest.flash`
To clean: `make clean`

## Software documentation
You can access the documentation generated from the code with doxygen (see the doxygen paragraph to generate it) in the doxygen/html or latex.

## Hardware documentation
Microcontroller used: STM32F303K8 on a Nulceo-32 board, main doc:
* [Reference Manual STM32F3 line, doc RM0316, 1141 pages](https://www.st.com/content/ccc/resource/technical/document/reference_manual/4a/19/6e/18/9d/92/43/32/DM00043574.pdf/files/DM00043574.pdf/jcr:content/translations/en.DM00043574.pdf)
    * memory map, p57, table 4
* [STM32F303x6/x8 Datasheet, 124 pages](https://www.st.com/content/ccc/resource/technical/document/datasheet/group3/38/c6/ca/d1/f7/d5/4e/30/DM00092070/files/DM00092070.pdf/jcr:content/translations/en.DM00092070.pdf)
    * alternate function, p41, table 14
* [Reference STM Nuleo-32 Board, doc UM1956, 37 pages](https://www.st.com/content/ccc/resource/technical/document/user_manual/e3/0e/88/05/e8/74/43/a0/DM00231744.pdf/files/DM00231744.pdf/jcr:content/translations/en.DM00231744.pdf)

## Doxygen

Generating the documentation with doxygen:
--> install doxygen on your system

--> run `doxygen doxygenConf` from the project directory

--> the documentation can then be read from doxygen/html/index.html in a browser

--> to generate the pdf for the github (or for yourself !) go into the latex directory `cd doxygen/latex` and run `make`.

Note: You must have a latex distribution on your computer that has `pdflatex` command.

## Generate the database for your IDE
--> to update the compile_command.json you can use bear (available in the AUR)
--> run `make clean`
--> run `bear /compilation command/`

## Debug with uart
--> install picocom
--> find your card `ls /dev` . It should be /dev/ttyACM0
--> run picocom with `picocom -b 9600 /dev/ttyACM0`

## Coding style

* Tabs are spaces = 4

* Column = 80

* Brackets :
    ```
    def peripheral_action_subjectofaction(params){
        code...
        some more code...
    }
    ```
* Function naming
    * _ is the separator
    * peripheral_action_subjectofaction
    * function starting with _ are private and should not be called in high level code
  
* Variables
    * my_var

* Documentation using doxygen
    * comment the function interface in the .h files (javadoc like)
    * detail the function in .c files

* We envision three levels for the code :
    * lowlevel fuctions that must be as general as possible to setup the hardware config (ex: timer fuctions)
    * lowlevel modules with the functions called by the user (ex: motor module, with setup and speed/dir fuctions)
    * rolling unit level (ex: control engineering)
