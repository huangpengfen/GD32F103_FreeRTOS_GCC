
# STD Defines
DDEFS += -DGD32F10X_HD -DUSE_STDPERIPH_DRIVER

# source director
GD32F1_STD_LIB     = $(GD32F10x_LIB_DIR)/GD32F10x_standard_peripheral
GD32F1_CORE_DIR    = $(GD32F10x_LIB_DIR)/CMSIS
GD32F1_DEVICE_DIR  = $(GD32F10x_LIB_DIR)/CMSIS/GD/GD32F10x/Source
GD32F1_SRC_DIR     = $(GD32F1_STD_LIB)/Source
GD32F1_INC_DIR     = $(GD32F1_STD_LIB)/Include

# startup
ASM_SRC  += $(GD32F1_DEVICE_DIR)/GCC/startup_gd32f10x_hd.S

# CMSIS
SRC  += $(GD32F1_DEVICE_DIR)/system_gd32f10x.c
#SRC  += $(GD32F1_CORE_DIR)/core_cm3.c
SRC  += $(GD32F10x_LIB_DIR)/syscalls.c

# use libraries, please add or remove when you use or remove it.
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_adc.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_bkp.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_can.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_crc.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_dac.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_dma.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_enet.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_exmc.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_exti.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_fmc.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_fwdgt.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_gpio.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_i2c.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_misc.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_pmu.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_rcu.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_rtc.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_sdio.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_spi.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_timer.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_usart.c
SRC  += $(GD32F1_SRC_DIR)/gd32f10x_wwdgt.c

# include directories
INCLUDE_DIRS += $(GD32F1_CORE_DIR)
INCLUDE_DIRS += $(GD32F1_DEVICE_DIR)
INCLUDE_DIRS += $(GD32F1_INC_DIR)
INCLUDE_DIRS += $(GD32F1_STD_LIB)

