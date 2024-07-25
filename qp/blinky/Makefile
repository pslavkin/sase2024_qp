PROJECT		:= blinky
QPC			:= ../qp/qpc
QP_PORT_DIR := $(QPC)/ports/arm-cm/qk/gnu

# C source files...
C_SRCS := \
		  main.c \
		  mem/mem.c \
		  mem/pool.c \
		  bsp/bsp.c \
		  uart/uart_drv.c \
		  uart/uart_sm.c \
		  uart/uart.c \
		  led/led_drv.c \
		  led/led_sm.c \
		  led/led.c \
		  btn/btn_drv.c \
		  btn/btn_sm.c \
		  btn/btn.c \
		  system_TM4C123GH6PM.c \
		  startup_TM4C123GH6PM.c

OUTPUT    := $(PROJECT)
LD_SCRIPT := bsp/linker.ld

# defines...
DEFINES   := -DTARGET_IS_TM4C123_RB1
# ARM CPU, ARCH, FPU, and Float-ABI types...
# ARM_CPU:	 [cortex-m0 | cortex-m0plus | cortex-m1 | cortex-m3 | cortex-m4]
# ARM_FPU:	 [ | vfp]
# FLOAT_ABI: [ | soft | softfp | hard]
#
ARM_CPU   := -mcpu=cortex-m4
ARM_FPU   := -mfpu=vfp
FLOAT_ABI := -mfloat-abi=softfp
CONF	  := dbg

#-----------------------------------------------------------------------------
C_SRCS += \
	qep_hsm.c \
	qep_msm.c \
	qf_act.c \
	qf_actq.c \
	qf_defer.c \
	qf_dyn.c \
	qf_mem.c \
	qf_ps.c \
	qf_qact.c \
	qf_qeq.c \
	qf_qmact.c \
	qf_time.c \
	qk.c \
	qk_port.c

QS_SRCS := \
	qs.c \
	qs_rx.c \
	qs_fp.c \
	#

# Typically you should not need to change anything below this line
VPATH	 += $(QPC)/src/qf  \
			$(QPC)/src/qk \
			$(QP_PORT_DIR) \
			$(QPC)/3rd_party/ek-tm4c123gxl \
			$(QPC)/3rd_party/ek-tm4c123gxl/gnu \

INCLUDES += -I. \
			-Ibsp/ \
			-I$(QPC)/include \
			-I$(QPC)/src	 \
			-I$(QP_PORT_DIR) \
			-I$(QPC)/3rd_party/CMSIS/Include \
			-I$(QPC)/3rd_party/ek-tm4c123gxl

#-----------------------------------------------------------------------------
# GNU-ARM toolset (NOTE: You need to adjust to your machine)
GNU_ARM := /usr

# make sure that the GNU-ARM toolset exists...
ifeq ("$(wildcard $(GNU_ARM))","")
$(error GNU_ARM toolset not found. Please adjust the Makefile)
endif

CC	  := $(GNU_ARM)/bin/arm-none-eabi-gcc
CPP   := $(GNU_ARM)/bin/arm-none-eabi-g++
AS	  := $(GNU_ARM)/bin/arm-none-eabi-as
LINK  := $(GNU_ARM)/bin/arm-none-eabi-gcc
BIN   := $(GNU_ARM)/bin/arm-none-eabi-objcopy


# basic utilities (included in Qtools for Windows), see:
#	 http://sourceforge.net/projects/qpc/files/Qtools

MKDIR := mkdir
RM	  := rm

#-----------------------------------------------------------------------------
# build options for various configurations for ARM Cortex-M4F
#

# combine all the sources...
C_SRCS += $(QP_SRCS)
ASM_SRCS += $(QP_ASMS)

ifeq (rel, $(CONF)) # Release configuration ..................................

BIN_DIR := build_rel
# gcc options:
CFLAGS	= -c -O3 -fno-pie -std=c11 -pedantic -Wall -Wextra -W \
	$(INCLUDES) $(DEFINES) -DNDEBUG

CPPFLAGS = -c -O3 -fno-pie -std=c++11 -pedantic -Wall -Wextra \
	-fno-rtti -fno-exceptions \
	$(INCLUDES) $(DEFINES) -DNDEBUG

else ifeq (spy, $(CONF))  # Spy configuration ................................

BIN_DIR := build_spy

C_SRCS	 += $(QS_SRCS)
VPATH	 += $(QPC)/src/qs

# gcc options:
CFLAGS	= -c -g -O -fno-pie -std=c11 -pedantic -Wall -Wextra -W \
	$(INCLUDES) $(DEFINES) -DQ_SPY

CPPFLAGS = -c -g -O -fno-pie -std=c++11 -pedantic -Wall -Wextra \
	-fno-rtti -fno-exceptions \
	$(INCLUDES) $(DEFINES) -DQ_SPY

else # default Debug configuration .........................................

BIN_DIR := build

ASFLAGS = -g $(ARM_CPU) $(ARM_FPU) $(ASM_CPU) $(ASM_FPU)

CFLAGS = -c -g $(ARM_CPU) $(ARM_FPU) $(FLOAT_ABI) -mthumb -Wall \
	-ffunction-sections -fdata-sections \
	-O $(INCLUDES) $(DEFINES)

CPPFLAGS = -c -g $(ARM_CPU) $(ARM_FPU) $(FLOAT_ABI) -mthumb -Wall \
	-ffunction-sections -fdata-sections -fno-rtti -fno-exceptions \
	-O $(INCLUDES) $(DEFINES)

endif # .....................................................................

LINKFLAGS = -T$(LD_SCRIPT) $(ARM_CPU) $(ARM_FPU) $(FLOAT_ABI) -mthumb \
	-specs=nosys.specs -specs=nano.specs \
	-Wl,-Map,$(BIN_DIR)/$(OUTPUT).map,--cref,--gc-sections $(LIB_DIRS)


ASM_OBJS     := $(patsubst %.s,%.o,  $(ASM_SRCS))
C_OBJS		 := $(patsubst %.c,%.o,   $(C_SRCS))
CPP_OBJS	 := $(patsubst %.cpp,%.o, $(CPP_SRCS))

TARGET_ELF   := $(BIN_DIR)/$(OUTPUT).elf
ASM_OBJS_EXT := $(addprefix $(BIN_DIR)/, $(ASM_OBJS))
C_OBJS_EXT	 := $(addprefix $(BIN_DIR)/, $(C_OBJS))
C_DEPS_EXT	 := $(patsubst %.o,%.d, $(C_OBJS_EXT))
CPP_OBJS_EXT := $(addprefix $(BIN_DIR)/, $(CPP_OBJS))
CPP_DEPS_EXT := $(patsubst %.o,%.d, $(CPP_OBJS_EXT))

# create $(BIN_DIR) if it does not exist
ifeq ("$(wildcard $(BIN_DIR))","")
$(shell $(MKDIR) $(BIN_DIR))
endif

#-----------------------------------------------------------------------------
# rules
#

all: $(TARGET_ELF)

$(TARGET_ELF) : $(ASM_OBJS_EXT) $(C_OBJS_EXT) $(CPP_OBJS_EXT)
	$(CC) $(CFLAGS) $(QPC)/src/qs/qstamp.c -o $(BIN_DIR)/qstamp.o
	$(LINK) $(LINKFLAGS) -o $@ $^ $(BIN_DIR)/qstamp.o $(LIBS)

$(BIN_DIR)/%.d : %.c
	$(CC) -MM -MT $(@:.d=.o) $(CFLAGS) $< > $@

$(BIN_DIR)/%.d : %.cpp
	$(CPP) -MM -MT $(@:.d=.o) $(CPPFLAGS) $< > $@

$(BIN_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/%.o : %.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

# include dependency files only if our goal depends on their existence
ifneq ($(MAKECMDGOALS),clean)
  ifneq ($(MAKECMDGOALS),show)
-include $(C_DEPS_EXT) $(CPP_DEPS_EXT)
  endif
endif


.PHONY : clean show
clean :
	find $(BIN_DIR) -iname "*\.o"  -delete && find $(BIN_DIR) -iname "*\.d" -delete 

show :
	@echo PROJECT	   = $(PROJECT)
	@echo TARGET_EXE   = $(TARGET_EXE)
	@echo VPATH		   = $(VPATH)
	@echo C_SRCS	   = $(C_SRCS)
	@echo CPP_SRCS	   = $(CPP_SRCS)
	@echo C_DEPS_EXT   = $(C_DEPS_EXT)
	@echo C_OBJS_EXT   = $(C_OBJS_EXT)
	@echo C_DEPS_EXT   = $(C_DEPS_EXT)
	@echo CPP_DEPS_EXT = $(CPP_DEPS_EXT)
	@echo CPP_OBJS_EXT = $(CPP_OBJS_EXT)
	@echo LIB_DIRS	   = $(LIB_DIRS)
	@echo LIBS		   = $(LIBS)
	@echo DEFINES	   = $(DEFINES)

