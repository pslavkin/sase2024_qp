PROJECT		:= blinky
QPC			:= ../qp/qpc
#QP_PORT_DIR := $(QPC)/ports/posix-qv
QP_PORT_DIR := $(QPC)/ports/posix/

# C source files...
C_SRCS := \
		  main.c \
		  qs/qs_posix.c \
		  share/signals.c \
		  mem/mem.c \
		  mem/pool.c \
		  bsp/bsp_posix.c \
		  uart/uart_drv_posix.c \
		  uart/uart_sm.c \
		  uart/uart.c \
		  led/led_drv_posix.c \
		  led/led_sm.c \
		  led/led.c \
		  btn/btn_drv_posix.c \
		  btn/btn_sm.c \
		  btn/btn.c \

# defines...
DEFINES   := -DPOSIX -DQF_CONSOLE
ifeq (spy, $(CONF)) # Release configuration ..................................
DEFINES   += -DQ_SPY
endif

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
	qf_port.c \

ifeq (spy, $(CONF))
C_SRCS += \
	qs.c \
	qs_64bit.c \
	qs_rx.c \
	qs_fp.c \
	qs_port.c
endif

LIBS += -lpthread

# Typically you should not need to change anything below this line
VPATH	 += $(QPC)/src/qf  \
			$(QP_PORT_DIR) \
			$(QPC)/src/qs \

INCLUDES += -I. \
			-I./share \
			-I$(QPC)/include \
			-I$(QPC)/src	 \
			-I$(QP_PORT_DIR) \

#-----------------------------------------------------------------------------
# GNU-ARM toolset (NOTE: You need to adjust to your machine)
CC	  := gcc
CPP   := g++
LINK  := gcc	# for C programs
#LINK  := g++	# for C++ programs

MKDIR	   := mkdir -p
RM		   := rm -f
TARGET_EXT :=

#-----------------------------------------------------------------------------
# build options for various configurations for ARM Cortex-M4F
#

BIN_DIR  := build
#
# gcc options:
CFLAGS  = -c -g -O -fno-pie -std=c11 -pedantic -Wall -Wextra -W \
	$(INCLUDES) $(DEFINES)

CPPFLAGS = -c -g -O -fno-pie -std=c++11 -pedantic -Wall -Wextra \
	-fno-rtti -fno-exceptions \
	$(INCLUDES) $(DEFINES)

LINKFLAGS := -no-pie


C_OBJS       := $(patsubst %.c,%.o,   $(C_SRCS))
CPP_OBJS     := $(patsubst %.cpp,%.o, $(CPP_SRCS))

TARGET_EXE   := $(BIN_DIR)/$(PROJECT)$(TARGET_EXT)
C_OBJS_EXT   := $(addprefix $(BIN_DIR)/, $(C_OBJS))
C_DEPS_EXT   := $(patsubst %.o,%.d, $(C_OBJS_EXT))
CPP_OBJS_EXT := $(addprefix $(BIN_DIR)/, $(CPP_OBJS))
CPP_DEPS_EXT := $(patsubst %.o,%.d, $(CPP_OBJS_EXT))

# create $(BIN_DIR) if it does not exist
ifeq ("$(wildcard $(BIN_DIR))","")
$(shell $(MKDIR) $(BIN_DIR))
endif

#-----------------------------------------------------------------------------
# rules
#

.PHONY: clean show

all: $(TARGET_EXE)

$(TARGET_EXE) : $(C_OBJS_EXT) $(CPP_OBJS_EXT)
	$(CC) $(CFLAGS) $(QPC)/src/qs/qstamp.c -o $(BIN_DIR)/qstamp.o
	$(LINK) $(LINKFLAGS) $(LIB_DIRS) -o $@ $^ $(BIN_DIR)/qstamp.o $(LIBS)

$(BIN_DIR)/%.d : %.c
	$(CC) -MM -MT $(@:.d=.o) $(CFLAGS) $< > $@

$(BIN_DIR)/%.d : %.cpp
	$(CPP) -MM -MT $(@:.d=.o) $(CPPFLAGS) $< > $@

$(BIN_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/%.o : %.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

# create BIN_DIR and include dependencies only if needed
ifneq ($(MAKECMDGOALS),clean)
  ifneq ($(MAKECMDGOALS),show)
     ifneq ($(MAKECMDGOALS),debug)
ifeq ("$(wildcard $(BIN_DIR))","")
$(shell $(MKDIR) $(BIN_DIR))
endif
-include $(C_DEPS_EXT) $(CPP_DEPS_EXT)
     endif
  endif
endif

clean :
	find $(BIN_DIR) -iname "*\.o"  -delete && find $(BIN_DIR) -iname "*\.d" -delete && find $(BIN_DIR) -iname "*\.elf" -delete

dirs:
	mkdir -p build/bsp 		\
			 build/led 		\
			 build/btn 		\
			 build/mem 		\
			 build/uart 	\
			 build/qs 		\
			 build/share 	\

show :
	@echo PROJECT      = $(PROJECT)
	@echo TARGET_EXE   = $(TARGET_EXE)
	@echo VPATH        = $(VPATH)
	@echo C_SRCS       = $(C_SRCS)
	@echo CPP_SRCS     = $(CPP_SRCS)
	@echo C_DEPS_EXT   = $(C_DEPS_EXT)
	@echo C_OBJS_EXT   = $(C_OBJS_EXT)
	@echo C_DEPS_EXT   = $(C_DEPS_EXT)
	@echo CPP_DEPS_EXT = $(CPP_DEPS_EXT)
	@echo CPP_OBJS_EXT = $(CPP_OBJS_EXT)
	@echo LIB_DIRS     = $(LIB_DIRS)
	@echo LIBS         = $(LIBS)
	@echo DEFINES      = $(DEFINES)

