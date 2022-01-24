
# toolchain
TOOLCHAIN    = arm-none-eabi-
CC           = $(TOOLCHAIN)gcc
CP           = $(TOOLCHAIN)objcopy
AS           = $(TOOLCHAIN)gcc -x assembler-with-cpp
HEX          = $(CP) -O ihex
BIN          = $(CP) -O binary -S

# define mcu, specify the target processor
MCU          = cortex-m3

# all the files will be generated with this name (main.elf, main.bin, main.hex, etc)
PROJECT_NAME=GD32F103

# specify define
DDEFS       =

# define root dir
ROOT_DIR     = .

# define include dir
INCLUDE_DIRS =

# define gd32f10x lib dir
GD32F10x_LIB_DIR      = $(ROOT_DIR)/Libraries

# define freertos dir
FREERTOS_DIR = $(ROOT_DIR)/Source/FreeRTOS

# define user dir
USER_DIR     = $(ROOT_DIR)/Source

# link file
LINK_SCRIPT  = $(ROOT_DIR)/Libraries/GD32F103RCTX_FLASH.ld

# user specific
SRC       =
ASM_SRC   =
SRC      += $(USER_DIR)/USER/main.c
SRC      += $(USER_DIR)/USER/gd32f10x_it.c
SRC      += $(USER_DIR)/BSP/UART/bsp_uart.c
SRC      += $(USER_DIR)/BSP/LED/bsp_led.c
SRC      += $(USER_DIR)/BSP/BspSystick/systick.c
SRC      += $(USER_DIR)/APP/app.c



# user include
INCLUDE_DIRS  = $(USER_DIR)

# include sub makefiles
include makefile_std_lib.mk   # GD32 Standard Peripheral Library
include makefile_freertos.mk  # freertos source

INC_DIR  = $(patsubst %, -I%, $(INCLUDE_DIRS))

# run from Flash
DEFS	 = $(DDEFS) -DRUN_FROM_FLASH=1

OBJECTS  = $(ASM_SRC:.S=.o) $(SRC:.c=.o)

# Define optimisation level here
OPT = -O0

MC_FLAGS = -mcpu=$(MCU)

LIBS = -lc -lm -lnosys
AS_FLAGS = $(MC_FLAGS) -g -gdwarf-2 -mthumb  -Wa,-amhls=$(<:.s=.lst)
CP_FLAGS = $(MC_FLAGS) $(OPT) -g -gdwarf-2 -mthumb -fomit-frame-pointer -Wall -fverbose-asm -Wa,-ahlms=$(<:.c=.lst) $(DEFS)
#LD_FLAGS = $(MC_FLAGS) -g -gdwarf-2 -mthumb -nostartfiles -Xlinker --gc-sections  -static -mfloat-abi=soft -T$(LINK_SCRIPT) -Wl,-Map=$(PROJECT_NAME).map,--cref,--no-warn-mismatch
#LD_FLAGS += -lc -lrdimon -u _printf_float
#LD_FLAGS += -L/home/hpf/Compile_chain/gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi/lib/libc.a
LD_FLAGS = -mthumb $(MC_FLAGS) -specs=nano.specs -T$(LINK_SCRIPT) $(LIBS) -Wl,-Map=$(PROJECT_NAME).map,--cref -Wl,--gc-sections -u _printf_float

#
# makefile rules
#
all: $(OBJECTS) $(PROJECT_NAME).elf  $(PROJECT_NAME).hex $(PROJECT_NAME).bin
	$(TOOLCHAIN)size $(PROJECT_NAME).elf

%.o: %.c
	$(CC) -c $(CP_FLAGS) -I . $(INC_DIR) $< -o $@

%.o: %.s
	$(AS) -c $(AS_FLAGS) $< -o $@

%.elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LD_FLAGS) -o $@

%.hex: %.elf
	$(HEX) $< $@

%.bin: %.elf
	$(BIN)  $< $@

flash: $(PROJECT_NAME).bin
	st-flash write $(PROJECT_NAME).bin 0x8000000

erase:
	st-flash erase

clean:
	-rm -rf $(OBJECTS)
	-rm -rf $(PROJECT_NAME).elf
	-rm -rf $(PROJECT_NAME).map
	-rm -rf $(PROJECT_NAME).hex
	-rm -rf $(PROJECT_NAME).bin
	-rm -rf $(SRC:.c=.lst)
	-rm -rf $(ASM_SRC:.S=.lst)

