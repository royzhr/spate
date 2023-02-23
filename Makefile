#
# Rodzhang
#
#

vpath %.c src


TARGET = ./build/spate

# Import source code directory
include mk/src_dir.mk
include mk/include.mk

include mk/src_dpdk_dir.mk
include mk/dpdk.mk
include mk/src_ebpf_dir.mk
include mk/ebpf.mk


#Debug configuration:
DEBUG_C_FLAGS = -DSPATE_DEBUG -g -O0
#Release configuration:
RELEASE_C_FLAGS = -g -O3

CFLAGS = -Wall -Werror -rdynamic $(D_INC)
LIBS = -lpthread -lm -lpcap -rdynamic 

ifeq ($(dpdk_enable), 1)
	SRC_DIR += $(DPDK_SRC_DIR)
	CFLAGS  += $(DPDK_CFLAGS) -DDPDK_ENABLE
	LIBS    += $(DPDK_DEP_LIBS)
endif

ifeq ($(ebpf_enable), 1)
	SRC_DIR += $(EBPF_SRC_DIR)
	CFLAGS += -DEBPF_ENABLE
	LIBS    += $(EBPF_DEP_LIBS)
endif


OBJ_DIR = $(foreach dir, $(SRC_DIR), $(addprefix build/, $(dir)))

SRC_C = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
OBJECT = $(addprefix build/, $(patsubst %.c, %.o, $(SRC_C)))


$(TARGET):$(OBJECT)
	gcc -g -rdynamic -o $@ $^ $(LIBS) 

$(OBJECT):$(SRC_C)
	gcc -c $(CFLAGS) $(patsubst %.o, %.c, $(subst build/, , $@)) -o $@


.PHONY: clean dir check debug release

debug: CFLAGS += $(DEBUG_C_FLAGS) 
release: CFLAGS += $(RELEASE_C_FLAGS) 

ifeq ($(ebpf_enable), 1)
debug: dir $(TARGET) $(EBPF_OBJ)
release: dir $(TARGET) $(EBPF_OBJ)
else
debug: dir $(TARGET)
release: dir $(TARGET)
endif

#Notice: Do not use variables for the rm commond! To avoid misoperation.
clean:
	rm -rf ./build

dir:
	mkdir -p $(OBJ_DIR)

install:
	cp $(TARGET) /usr/local/bin/

.DEFAULT_GOAL := help

help:
	@echo ""
	@echo "This is the document that tells you how to make:"
	@echo ""
	@echo "Compile on Linux platform, can use command:"
	@echo "   \033[1;37m make debug \033[0m                  : compile debug   version"
	@echo "   \033[1;37m make release \033[0m                : compile release version"
	@echo ""
	@echo "Compile with DPDK(support Linux and DPDK), can use command:"
	@echo "   \033[1;37m make dpdk_enable=1 debug \033[0m    : compile debug   version"
	@echo "   \033[1;37m make dpdk_enable=1 release \033[0m  : compile release version"
	@echo "Note: Make sure you have installed \033[1;31mDPDK-20.11\033[0m in your system if you want to build with DPDK."
	@echo ""
	@echo "Compile with eBPF-offload on Linux, can use command:"
	@echo "   \033[1;37m make ebpf_enable=1 debug \033[0m    : compile debug   version"
	@echo "   \033[1;37m make ebpf_enable=1 release \033[0m  : compile release version"
	@echo "Note: Make sure you have installed \033[1;31mlibbpf\033[0m in your system if you want to build with eBPF offload."
	@echo ""
	@echo "Compile with all feature(support eBPF,DPDK), can use command:"
	@echo "   \033[1;37m make dpdk_enable=1 ebpf_enable=1 debug \033[0m    "
	@echo "   \033[1;37m make dpdk_enable=1 ebpf_enable=1 release \033[0m  "
	@echo ""
	@echo "How to clean, use command:"
	@echo "   \033[1;37m make clean \033[0m                  : clean all compiled objects"
	@echo ""
	@echo "How to install, use command:"
	@echo "   \033[1;37m make install \033[0m                : install to /usr/local/bin"
	@echo ""
	@echo "Note: Please make clean before make if you have already complied before, "
	@echo "For example, you can enter: \033[0;33m make clean; make release -j 8 \033[0m "
	@echo ""
	@echo ""

check:
ifeq ($(dpdk_enable), 1)
	@echo "dpdk enable"
else
	@echo "dpdk disable"
endif
ifeq ($(ebpf_enable), 1)
	@echo "ebpf enable"
else
	@echo "ebpf disable"
endif



