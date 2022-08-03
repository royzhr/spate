#
# Rodzhang
#
# EBPF's make
#


EBPF_DEP_LIBS = -lbpf


EBPF_SRC_C = $(wildcard ebpf/src/*.c)
EBPF_OBJ = $(addprefix build/, $(patsubst %.c, %.o, $(notdir $(EBPF_SRC_C))))


$(EBPF_OBJ): $(EBPF_SRC_C)
	clang -O2 -Wall -target bpf -c $(patsubst %.o, %.c, $(subst build/, ebpf/src/, $@)) -o $@


ebpf_dir: 
	mkdir -p ./build

ebpf: ebpf_dir $(EBPF_OBJ) 
