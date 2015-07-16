################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include acs712/subdir.mk
-include UART/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
FLASH_IMAGE += \
current_reader_device.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: current_reader_device.elf secondary-outputs

# Tool invocations
current_reader_device.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,current_reader_device.map -mmcu=atmega328p -o "current_reader_device.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

current_reader_device.hex: current_reader_device.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex current_reader_device.elf  "current_reader_device.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: current_reader_device.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p current_reader_device.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: current_reader_device.elf
	@echo 'Invoking: AVRDude'
	/usr/bin/avrdude -pm328p -cavrispmkII -B10 -u -Uflash:w:current_reader_device.hex:a -Ulfuse:w:0xe2:m -Uhfuse:w:0xd9:m -Uefuse:w:0x7:m
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(C_DEPS) current_reader_device.elf
	-@echo ' '

secondary-outputs: $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
