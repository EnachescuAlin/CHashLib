CC = gcc
INCLUDE_PATH = -I../../../include
CFLAGS = -Wall -Wextra
SOFLAGS =

SRC_DIR = ../../../src
TEST_DIR = ../../../test
BIN_DIR = ../../../bin/linux/make/$(CONFIG)

_LIB_OBJ = md5.o
LIB_OBJ = $(patsubst %,$(BIN_DIR)/%,$(_LIB_OBJ))

_TEST_OBJ = CHashLib_test.o test_md5.o
TEST_OBJ = $(patsubst %,$(BIN_DIR)/%,$(_TEST_OBJ))

SHARED = false

prepare_env:
ifndef CONFIG
	$(error CONFIG not defined)
endif
	mkdir -p ../../../bin/linux/make/$(CONFIG)
ifeq ($(CONFIG),release_32_static)
PLATFORM = -m32
EXTRA_FLAGS = -O2
endif
ifeq ($(CONFIG),release_32_shared)
PLATFORM = -m32
EXTRA_FLAGS = -O2
SHARED = true
SOFLAGS = -fPIC
endif
ifeq ($(CONFIG),release_64_static)
PLATFORM = -m64
EXTRA_FLAGS = -O2
endif
ifeq ($(CONFIG),release_64_shared)
PLATFORM = -m64
EXTRA_FLAGS = -O2
SHARED = true
SOFLAGS = -fPIC
endif
ifeq ($(CONFIG),debug_32_static)
PLATFORM = -m32
EXTRA_FLAGS = -g
endif
ifeq ($(CONFIG),debug_32_shared)
PLATFORM = -m32
EXTRA_FLAGS = -g
SHARED = true
SOFLAGS = -fPIC
endif
ifeq ($(CONFIG),debug_64_static)
PLATFORM = -m64
EXTRA_FLAGS = -g
endif
ifeq ($(CONFIG),debug_64_shared)
PLATFORM = -m64
EXTRA_FLAGS = -g
SHARED = true
SOFLAGS = -fPIC
endif

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(SOFLAGS) $(PLATFORM) $(EXTRA_FLAGS) $(INCLUDE_PATH)

$(BIN_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(PLATFORM) $(EXTRA_FLAGS) $(INCLUDE_PATH)

build_lib:
ifeq ($(SHARED),false)
	ar rcs $(BIN_DIR)/libCHashLib.a $(LIB_OBJ)
else
	$(CC) -shared $(PLATFORM) $(LIB_OBJ) -o $(BIN_DIR)/libCHashLib.so
endif

build_test:
	$(CC) $(TEST_OBJ) $(PLATFORM) -L$(BIN_DIR) -lCHashLib -o $(BIN_DIR)/CHashLib_test

build: prepare_env $(LIB_OBJ) $(TEST_OBJ) build_lib build_test
	$(info ***** build completed successfully *****)
ifeq ($(SHARED),true)
	LD_LIBRARY_PATH=$(shell pwd)/$(BIN_DIR) $(BIN_DIR)/CHashLib_test
else
	$(BIN_DIR)/CHashLib_test
endif

clean: 
ifdef CONFIG
	rm -f -r ../../../bin/linux/make/$(CONFIG)
else
	rm -f -r ../../../bin/linux/make/release_32_static
	rm -f -r ../../../bin/linux/make/release_32_shared
	rm -f -r ../../../bin/linux/make/release_64_static
	rm -f -r ../../../bin/linux/make/release_64_shared
	rm -f -r ../../../bin/linux/make/debug_32_static
	rm -f -r ../../../bin/linux/make/debug_32_shared
	rm -f -r ../../../bin/linux/make/debug_64_static
	rm -f -r ../../../bin/linux/make/debug_64_shared
endif
