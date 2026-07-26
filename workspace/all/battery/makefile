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

include ../../$(PLATFORM)/platform/makefile.env
SDL?=SDL

###########################################################

TARGET = battery
INCDIR = -I. -I../common/ -I../../$(PLATFORM)/platform/
# Shared common/ + platform stay C; the tool itself is C++20. Compile the C
# units to objects, then compile the .cpp and link everything through g++.
SOURCE = -c ../common/utils.c ../common/api.c ../common/config.c ../common/scaler.c ../../$(PLATFORM)/platform/platform.c
CXXSOURCE = $(TARGET).cpp
CXXSOURCE += build/$(PLATFORM)/utils.o build/$(PLATFORM)/api.o build/$(PLATFORM)/config.o build/$(PLATFORM)/scaler.o build/$(PLATFORM)/platform.o

CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
# Prefer real C++20; fall back to gnu++2a on older toolchains (e.g. the current
# gcc 8.3 tg5040 cross-compiler, which predates the -std=gnu++20 spelling).
CXXSTD := $(shell printf 'int main(){return 0;}' | $(CXX) -std=gnu++20 -x c++ - -o /dev/null >/dev/null 2>&1 && echo gnu++20 || echo gnu++2a)
CFLAGS  += $(OPT)
CFLAGS  += $(INCDIR) -DPLATFORM=\"$(PLATFORM)\"
CXXFLAGS += $(CFLAGS) -std=$(CXXSTD)
LDFLAGS	 += -lmsettings -lbatmondb -lsqlite3

PRODUCT= build/$(PLATFORM)/$(TARGET).elf

all: $(PREFIX_LOCAL)/include/batmondb.h
	mkdir -p build/$(PLATFORM)
	$(CC) $(SOURCE) $(CFLAGS) $(LDFLAGS)
	mv utils.o api.o config.o scaler.o platform.o build/$(PLATFORM)
	$(CXX) $(CXXSOURCE) -o $(PRODUCT) $(CXXFLAGS) $(LDFLAGS) -lstdc++
clean:
	rm -f $(PRODUCT)

$(PREFIX_LOCAL)/include/batmondb.h:
	cd ../libbatmondb && make