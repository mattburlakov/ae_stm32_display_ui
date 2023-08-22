# path to st-flash (or should be specified in PATH)
ST_FLASH ?= st-flash

######################################
# target
######################################
TARGET = test-g474

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
# OPT = -Og
OPT = -Os

#######################################
# paths
# path to STM32G474 standard peripheral library
STD_PERIPH_LIBS ?= ./Src/Drivers
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Src/main.c \
$(STD_PERIPH_LIBS)/CMSIS/Device/ST/STM32G4xx/Source/Templates/system_stm32g4xx.c

# ASM sources
ASM_SOURCES =  \
$(STD_PERIPH_LIBS)/CMSIS/Device/ST/STM32G4xx/Source/Templates/gcc/startup_stm32g474xx.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)g++
AS = $(GCC_PATH)/$(PREFIX)g++ -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
DUMP = $(GCC_PATH)/$(PREFIX)objdump
else
CC = $(PREFIX)g++
AS = $(PREFIX)g++ -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
DUMP = $(PREFIX)objdump
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
LSS = $(DUMP) -h -S -z
LSSD = $(DUMP) -h -d
#LSSD = $(DUMP) -d -marm
#######################################
# specify compiler flags
# CFLAGS
#######################################
# CFLAGS  = -g -O2 -Wall

# cpu
CPU = -mcpu=cortex-m4


# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# C STANDARD
CSTANDARD = -std=c++17

# macros for gcc
# AS defines
AS_DEFS =

# C defines
C_DEFS =  \
-DSTM32G474xx


# AS includes
AS_INCLUDES =

# C includes
C_INCLUDES =  \
-I. \
-I$(STD_PERIPH_LIBS)/CMSIS/Device/ST/STM32G4xx/Include/ \
-I$(STD_PERIPH_LIBS)/CMSIS/Core/Include/

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
# -mlittle-endian
CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

CFLAGS += $(CSTANDARD)

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

#CFLAGS += -DSTM32G474xx
#CFLAGS += -DGCC_ARMCM4
#CFLAGS += -DVECT_TAB_FLASH

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = ./Src/Linker/STM32G474CEUx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys
LIBDIR =
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# вывод информации линкером о ресурсах
LDFLAGS += -Wl,--print-memory-usage
#
#LDFLAGS += -mcpu=cortex-m4 -mthumb
#LDFLAGS += -nostartfiles -nostdlib
#LDFLAGS += -Wl,-Map=$(TARGET).map
#LDFLAGS += -L Linker -T ./Linker/STM32G474CEUX_FLASH.ld
#
#all: $(PROJECT).elf
#
## compile
#$(PROJECT).elf: $(SOURCES)
#	$(CC) $(CFLAGS) $^ -o $@
#	$(OBJCOPY) -O ihex $(PROJECT).elf $(PROJECT).hex
#	$(OBJCOPY) -O binary $(PROJECT).elf $(PROJECT).bin
#	$(OBJDUMP) -h -S -z $(PROJECT).elf > $(PROJECT).lss
#
## Create extended listing file from ELF output file.
#%.lss: %.elf
#	@echo
#	@echo $(MSG_EXTENDED_LISTING) $@
#	$(OBJDUMP) -h -S -z $< > $@
#	$(OBJDUMP) -h -d $< > $@d
#


# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).lss $(BUILD_DIR)/$(TARGET).lssd


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR)/%.lss: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(LSS) $< > $@

$(BUILD_DIR)/%.lssd: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(LSSD) $< > $@

$(BUILD_DIR):
	mkdir $@

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# flash
burn:
	$(ST_FLASH) --reset write $(BUILD_DIR)/$(TARGET).bin 0x8000000
# *** EOF ***
