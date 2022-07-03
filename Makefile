MAKEFLAGS += --no-builtin-rules

TARGET=bcc
PROG_DIR=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
INCLUDE:=-I$(PROG_DIR)/include/
KPROG_SRC:=$(wildcard src/kprog/*.bpf.c)
UPROG_SRC:=$(filter-out src/uprog/bcc.cpp, $(wildcard src/uprog/*.cpp))

INCLUDE+=-I/home/l0calh0st/lib
LIBRARY+=/home/l0calh0st/lib/bpf/libbpf.so

CC=clang
CFLAGS+=-g -O3
BPFTOOL:=/usr/local/bin/bpftool



.PHONY: skel

.PHONY: $(TARGET)
$(TARGET): skel $(UPROG_SRC:.cpp=.o)
	$(CC) $(CFLAGS) -lstdc++  -std=c++11 $(INCLUDE) $(LIBRARY) $(filter-out skel bcc.o,$^) src/uprog/bcc.cpp -lelf -o $(TARGET)

%.o: %.cpp
	$(CC) -lstdc++  -std=c++11 $(CFLAGS) $(INCLUDE) -c $^ -o $@


.PHONY: skel
skel: bpf $(KPROG_SRC:.bpf.c=.skel.h)

.PHONY: bpf
bpf: vmlinux $(KPROG_SRC:.c=.o)

.PHONY: vmlinux
vmlinux:
	$(BPFTOOL) btf dump file /sys/kernel/btf/vmlinux format c > $(PROG_DIR)/include/vmlinux.h

%.skel.h: %.bpf.o
	$(BPFTOOL) gen skeleton $^ name $(patsubst %.skel.h,skel_%, $(notdir $@)) > $(PROG_DIR)/include/$(notdir $(patsubst %.bpfo,%.skel.h, $@))

%.bpf.o: %.bpf.c
	$(CC) $(CFLAGS) $(INCLUDE) -target bpf  -D__TARGET_ARCH_x86 -c $(filter-out vmlinux, $^) -o $@

.PHONY: clean
clean:
	$(RM) include/vmlinux.h  include/*.skel.h
	$(RM) src/kprog/*.o src/uprog/*.o 
	$(RM) $(TARGET)
