PROJECT=testable

BUILD_DIR=bin
READY_BINARY=mcu
LINKER_SCRIPT=link.ld
SOURCE_FILES=src

INC=-Iinc

ARCH_FLAGS ?= -mthumb -mcpu=cortex-m3
CFLAGS ?= $(ARCH_FLAGS) -Wall -ffunction-sections -fdata-sections -fno-builtin -W -Wextra \
		  -Werror -Wundef -Wshadow -Wdouble-promotion -g3 -Os -Wformat-truncation -fno-common

LDFLAGS ?= -T $(LINKER_SCRIPT) -Wl,--gc-sections -Wl,-Map=$(READY_BINARY)/$(PROJECT).map -nostartfiles -nostdlib 

SOURCES=$(shell find $(SOURCE_FILES) -name '*.c')
OBJS=$(SOURCES:$(SOURCE_FILES)/%.c=$(BUILD_DIR)/%.o)

all: $(READY_BINARY)/$(PROJECT).bin $(OBJS)

$(BUILD_DIR)/%.o: $(SOURCE_FILES)/%.c
	mkdir -p $(dir $@)
	arm-none-eabi-gcc $(CFLAGS) $(INC) -c -o $@ $<

$(READY_BINARY)/$(PROJECT).bin: $(READY_BINARY)/$(PROJECT).elf
	arm-none-eabi-objcopy -O binary $< $@

$(READY_BINARY)/$(PROJECT).elf: $(OBJS)
	mkdir -p $(dir $@)
	arm-none-eabi-gcc $(LDFLAGS) $^ $(CFLAGS) $(INC) -o $@

.PHONY: clean

clean:
	rm -r $(READY_BINARY) 2> /dev/null ; rm -r $(BUILD_DIR) 2> /dev/null

load:
	st-flash --reset write $(READY_BINARY)/$(PROJECT).bin 0x08000000

erase:
	st-flash erase
