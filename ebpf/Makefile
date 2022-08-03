#
# Rodzhang
#
# ebpf's make
#



SRC_DIR = src
OBJ_DIR = object

SRC_C =  $(wildcard src/*.c)
OBJECT = $(addprefix ../build/, $(patsubst %.c, %.o, $(notdir $(SRC_C))))

#$(warning SRC_C: $(SRC_C))

dir :
	mkdir -p ../build

ebpf :dir $(OBJECT)
	echo "make ebpf"

$(OBJECT):$(SRC_C)
	clang -O2 -Wall -target bpf -c $(patsubst %.o, %.c, $(subst ../build/, src/, $@)) -o $@


clean:
	rm -f ../build/*.o

.DEFAULT_GOAL := ebpf
