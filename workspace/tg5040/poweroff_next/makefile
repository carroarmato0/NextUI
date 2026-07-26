###########################################################

ifeq (,$(PLATFORM))
PLATFORM=$(UNION_PLATFORM)
endif

ifeq (,$(PLATFORM))
	$(error please specify PLATFORM, eg. PLATFORM=trimui make)
endif

ifeq (,$(CROSS_COMPILE))
	$(error missing CROSS_COMPILE for this toolchain)
endif

###########################################################

include ../platform/makefile.env

###########################################################

TARGET = poweroff_next
INCDIR = -I. -I../../all/common -I../platform
# common/ utils + config are C++20 now; poweroff_next.c stays C. Compile the
# tool as C, the common units as C++20, and link through g++.
CSOURCE = -c $(TARGET).c
CXXSOURCE = ../../all/common/utils.cpp ../../all/common/config.cpp

CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
CXXSTD := $(shell printf 'int main(){return 0;}' | $(CXX) -std=gnu++20 -x c++ - -o /dev/null >/dev/null 2>&1 && echo gnu++20 || echo gnu++2a)
# Override CFLAGS and LDFLAGS to not include SDL2 dependencies
CFLAGS = $(OPT) -g -std=gnu11 -Wall -Wextra
CFLAGS += $(INCDIR) -DPLATFORM=\"$(PLATFORM)\"
CXXFLAGS = $(OPT) -g $(INCDIR) -DPLATFORM=\"$(PLATFORM)\" -std=$(CXXSTD)
LDFLAGS = -lpthread -ldl

PRODUCT = build/$(PLATFORM)/$(TARGET).elf

all:
	mkdir -p build/$(PLATFORM)
	$(CC) $(CSOURCE) $(CFLAGS)
	mv $(TARGET).o build/$(PLATFORM)
	$(CXX) build/$(PLATFORM)/$(TARGET).o $(CXXSOURCE) -o $(PRODUCT) $(CXXFLAGS) $(LDFLAGS) -lstdc++

clean:
	rm -f $(PRODUCT)
