# PES Project 2 Readme

**Team Members:** 
- Prayag Milan Desai
- Rahul Ramaprasad 


---

**Description of repository contents:**  
>This repository contains nine folders, each having multiple source and header files. The description of the folders are as follows:  

**Folder board:**  
This folder contains the library and source files related to the KL25Z FRDM board which have pin init functions and configuration functions. 

**Folder CMSIS:**  
This folder contains source and header files which provide interfaces to processor and peripherals, real-time operating systems, and middleware components.

**Folder drivers:**  
This folder contains drivers for clock, gpio, communication protocols, touch sensor, timer, flash,etc.

**Folder utilities:** 
This folder contains source and header file which facilitate the debugging process.

**Folder source_common:** 
This folder contains source files which are common to all targets and are compiled based on the macro definitions. The application is made
modular by defining multiple source files and are placed in target specific includes folder. The main.c is defined here, which is compiled 
for all targets.

**Folder frdm_includes:** 
This folder contains user defined source and header files which contain functions which are specific only to the FRDM board such as blinking
LEDs, touch sensor detection, RTC Timestamp.

**Folder pc_includes:** 
This folder contains user defined source and header files which contain functions which are specific only to the PC such as printing
LED status, Timestamp.

---

**Installation/execution notes for the C code in this repository:**  
All the code in this repository should be executed using the following command:  

- 'make "target"'  
Where, "target" has four choices
- frdm_release  
- frdm_debug  
- pc_release  
- pc-debug  
Always run the 'make clean' command before rebuilding other targets.
Executing the above command results in .exe file which can be executed on the pc target and .axf file which can be executed on FRDM board.  
This project has the following requirements, that are fulfilled using the aforementioned command:  
- ARM-GCC cross-compiler : The 'arm-none-eabi-gcc' command is used to compile the FRDM board target code
- Macro flag : The '-D $(target_macro_definition)' to compile the target specific sections of code 
- No errors and warnings: The -Wall flag enables a set of warnings, and the -Werror flag treats the warnings as errors. Since the output of the compiler shows no error, the code in this repo is without any compiler warnings and errors
