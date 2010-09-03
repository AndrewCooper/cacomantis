################################################################################
# Project Makefile for Cacomantis (Rock Band Robot) 
################################################################################

################################################################################
# Project Variables 
################################################################################

# Project name
PROJECT = cacomantis

# CPU architecture
MCU = at90usb1287

# Build Directory
OUTPUT = build

# Include Directories
INCLUDES =  -I"."\
			-I"conf"\
			-I"arch/at90usb128"\
			-I"arch/common"\

# Source files
CSRCS = \
    main.c\
    hid_task.c\
    snap_task.c\
    usb_descriptors.c\
    usb_specific_request.c\
    arch/at90usb128/lib_board/usb_key/usb_key.c\
    arch/at90usb128/lib_mcu/usart/usart.c\
    arch/at90usb128/lib_mcu/usb/usb_drv.c\
    arch/at90usb128/lib_mcu/util/start_boot.c\
    arch/at90usb128/modules/usb/device_chap9/usb_device_task.c\
    arch/at90usb128/modules/usb/device_chap9/usb_standard_request.c\
    arch/at90usb128/modules/usb/usb_task.c\
    arch/common/lib_mcu/wdt/wdt_drv.c\
    arch/common/modules/scheduler/scheduler.c\

#    arch/at90usb128/lib_mcu/usart/usart.c\

# Assembler source files
ASSRCS = \

################################################################################
# Compile Variables 
################################################################################

# Compiler
CC = avr-gcc

# Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU) -MD -MP -MF $(OUTPUT)/$(*).d

# Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -std=c99 -Wall -gdwarf-2 -Os -fsigned-char -ffunction-sections

# Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

# Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += -Wl,-Map=$(PROJECT).map,--cref,--gc-sections,--relax

# Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

# Eeprom file production flags
HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0

################################################################################
# Derived Variables 
################################################################################

# Target name
TARGET = $(PROJECT).elf

# Object files in build directory
OBJECTS := $(CSRCS:.c=.o) $(ASSRCS:.s=.o)
OBJECTS := $(addprefix $(OUTPUT)/,$(OBJECTS))

# Dependency files in build directory
DEPS = $(OBJECTS:.o=.d)

# Tell make where to look for files
VPATH = $(OUTPUT)

################################################################################
# Rules 
################################################################################

# Default Rule
.PHONY: all
all: $(TARGET) $(PROJECT).hex size

# Cleanup build products
.PHONY: clean
clean:
	@echo "Clean project"
	-rm -rf $(OUTPUT) $(PROJECT).elf $(PROJECT).hex $(PROJECT).eep $(PROJECT).map

# Rebuild the project
.PHONY: rebuild
rebuild: clean all

# Include Compiler-generated Prerequisites
-include $(DEPS)

# Compile: create object files from C source files.
$(OUTPUT)/%.o: %.c
	@echo 'Building file: $<'
	@mkdir -p $(dir $@) 2>/dev/null
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $(@)
	@echo
	
# Preprocess & assemble: create object files from assembler source files.
$(OUTPUT)/%.o: %.s
	@echo 'Building file: $<'
	@mkdir -p $(dir $@) 2>/dev/null
	@$(CC) $(INCLUDES) $(ASMFLAGS) -c $< -o $(@)
	@echo

# Link: bring object files together into a final executable
$(TARGET): $(OBJECTS)
	@echo "Linking"
	@$(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)
	@echo

# Hexify: convert executable into Intel-Hex format
%.hex: $(TARGET)
	@echo "Create hex file"
	@avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@
	@echo

# EEPify: convert executable into EEP format
%.eep: $(TARGET)
	@echo "Create eep file"
	@avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@  || exit 0
	@echo

# LSSify: convert executable into LSS format
%.lss: $(TARGET)
	@echo "Create lss file"
	@avr-objdump -h -S $< > $@
	@echo

# Size: Tell memory usage of the executable
size: ${TARGET}
	@avr-size -C --mcu=${MCU} ${TARGET}

