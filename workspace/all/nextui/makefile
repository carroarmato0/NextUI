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

TARGET = nextui
INCDIR = -I. -I../common/ -I../../$(PLATFORM)/platform/

# C and C++ translation units are listed separately. C files compile as C;
# C++ files compile as C++; everything links through g++ so the two can mix
# as modules are migrated to C++ incrementally.
CSOURCE = ../common/scaler.c ../common/utils.c ../common/config.c ../common/api.c ../../$(PLATFORM)/platform/platform.c
CXXSOURCE = $(TARGET).cpp

CC  = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
CFLAGS   += $(OPT)
CFLAGS   += $(INCDIR) -DPLATFORM=\"$(PLATFORM)\"
# CXXFLAGS inherits the platform CFLAGS (SDL/GL/PREFIX include paths) before the
# C-only -std is appended, so C++ TUs get the same include/define environment.
CXXFLAGS += $(CFLAGS) -std=gnu++20
CFLAGS   += -std=gnu99
LDFLAGS	 += -lmsettings

OBJ_DIR = build/$(PLATFORM)
OBJS = $(addprefix $(OBJ_DIR)/,$(notdir $(CSOURCE:.c=.o))) \
       $(addprefix $(OBJ_DIR)/,$(notdir $(CXXSOURCE:.cpp=.o)))

PRODUCT= build/$(PLATFORM)/$(TARGET).elf

# Locate sources across their directories so a single pattern rule suffices.
vpath %.c   . ../common ../../$(PLATFORM)/platform
vpath %.cpp . ../common ../../$(PLATFORM)/platform

all: $(PREFIX_LOCAL)/include/msettings.h $(PRODUCT)

$(PRODUCT): $(OBJS)
	$(CXX) $(OBJS) -o $(PRODUCT) $(LDFLAGS) -lstdc++

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(PRODUCT) $(OBJS)

$(PREFIX_LOCAL)/include/msettings.h:
	cd ../../$(PLATFORM)/libmsettings && make
