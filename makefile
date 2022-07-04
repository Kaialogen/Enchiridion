PROG = enchiridion
CC = gcc

NPROCS = $(shell grep -c 'processor' /proc/cpuinfo)
MAKEFLAGS += -j$(NPROCS)

include common.mk

CXXFLAGS += `sdl2-config --cflags`
CXXFLAGS += -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=maybe-uninitialized -Warray-bounds
CXXFLAGS += -g -lefence

LDFLAGS += `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
