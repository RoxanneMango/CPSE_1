CXX = ..\arduino\tools\arm-none-eabi-gcc\4.8.3-2014q1\bin\arm-none-eabi-g++
CXX_NATIVE = g++
CXXFLAGS = -c -g -Os -Wall -Wextra -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10813 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON -I..\arduino\hardware\sam\1.6.12\system\libsam -I..\arduino\hardware\sam\1.6.12\system\CMSIS\CMSIS\Include -I..\arduino\hardware\sam\1.6.12\system\CMSIS\Device\ATMEL -I..\arduino\hardware\sam\1.6.12\cores\arduino -I..\arduino\hardware\sam\1.6.12\variants\arduino_due_x
CXXFLAGS_NATIVE = -std=c++17
CC = ..\arduino\tools\arm-none-eabi-gcc\4.8.3-2014q1\bin\arm-none-eabi-gcc
CFLAGS = -c -g -Os -Wall -Wextra -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -Dprintf=iprintf -MMD -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10813 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON "-DUSB_MANUFACTURER=\"Arduino LLC\"" "-DUSB_PRODUCT=\"Arduino Due\"" -I..\arduino\hardware\sam\1.6.12\system\libsam -I..\arduino\hardware\sam\1.6.12\system\CMSIS\CMSIS\Include -I..\arduino\hardware\sam\1.6.12\system\CMSIS\Device\ATMEL -I..\arduino\hardware\sam\1.6.12\cores\arduino -I..\arduino\hardware\sam\1.6.12\variants\arduino_due_x
C_ASM_FLAGS = -c -g -x assembler-with-cpp -MMD -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10813 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -DSAM3_SERIES -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON -I..\arduino\hardware\sam\1.6.12\system\libsam -Iarduino\hardware\sam\1.6.12\system\CMSIS\CMSIS\Include -I..\arduino\hardware\sam\1.6.12\system\CMSIS\Device\ATMEL -Iarduino\hardware\sam\1.6.12\cores\arduino -I..\arduino\hardware\sam\1.6.12\variants\arduino_due_x
AR = ..\arduino\tools\arm-none-eabi-gcc\4.8.3-2014q1\bin\arm-none-eabi-ar
AR_NATIVE = ar
OBJC = ..\arduino\tools\arm-none-eabi-gcc\4.8.3-2014q1\bin\arm-none-eabi-objcopy
SIZE = ..\arduino\tools\arm-none-eabi-gcc\4.8.3-2014q1\bin\arm-none-eabi-size
PREFIX = ..\arduino_build
OUTPUT = build

OBJECTS = main.o
ASM_OBJECTS = decode_asm.o
EXEC = main

.PHONY: src lib flash all clean native printer lzw compress decompress compress_asm

src: $(OBJECTS) $(ASM_OBJECTS) compress_asm
	@echo ("Linking everything together . . .")
	$(CXX) -mcpu=cortex-m3 -mthumb -Os -Wl,--gc-sections -T..\arduino\hardware\sam\1.6.12\variants\arduino_due_x\linker_scripts\gcc\flash.ld "-Wl,-Map,$(OUTPUT)\mapping.map" -o $(OUTPUT)\$(EXEC).elf -L$(OUTPUT) -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -Wl,--start-group -u _sbrk -u link -u _close -u _fstat -u _isatty -u _lseek -u _read -u _write -u _exit -u kill -u _getpid $(PREFIX)\core\variant.o ..\arduino\hardware\sam\1.6.12\variants\arduino_due_x\libsam_sam3x8e_gcc_rel.a $(PREFIX)\core\core.a $(OUTPUT)\archive.a -Wl,--end-group -lm -lgcc
	$(OBJC) -O binary $(OUTPUT)\$(EXEC).elf $(OUTPUT)\$(EXEC).bin
	$(SIZE) -A $(OUTPUT)\$(EXEC).elf

$(OBJECTS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(OUTPUT)\$@
	$(AR) rcs $(OUTPUT)\archive.a $(OUTPUT)\$@

$(ASM_OBJECTS): %.o: %.S
	$(CXX) $(C_ASM_FLAGS) $< -o $(OUTPUT)\$@
	$(AR) rcs $(OUTPUT)\archive.a $(OUTPUT)\$@

lzw:
	$(CXX_NATIVE) $(CXXFLAGS_NATIVE) -o $(OUTPUT)/LZW LZW.cpp
	
compress: lzw
	cd $(OUTPUT) && LZW -c ..\input.txt ..\compressed.txt && cd ..

decompress: lzw
	cd $(OUTPUT) && LZW -d ..\compressed.txt ..\decompressed.txt && cd ..

compress_asm : compress
	cd $(OUTPUT) && LZW -a ..\input.txt ..\compressed.S && cd ..

flash:
	@echo ("Forcing reset with port-bump of 1200 bps . . .");
	py ..\arduino\tools\bossac\1.6.1-arduino\open_close_port.py
	@echo ("Writing binary to the arduino due . . .");
	..\arduino\tools\bossac\1.6.1-arduino\bossac.exe -i -d --port=COM3 -U false -e -w -v -b $(OUTPUT)\$(EXEC).bin -R 
	PuTTY.exe -serial COM3
clean: 
	@echo ("Initiating lemon pledge . . .");
	cd $(OUTPUT) && del *.o *.bin *.elf *.map *.d *.a *.exe
	@echo ("I clean . . .");
	
all: lib src flash