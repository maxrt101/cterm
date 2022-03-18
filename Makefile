
export TOPDIR := $(shell pwd)
export PREFIX ?= $(TOPDIR)/build
export BUILD  := $(TOPDIR)/build
export CC     := g++
export AR     := ar
export CFLAGS := -std=c++17 -I$(BUILD)/include

TARGET := $(PREFIX)/lib/libcterm.a
SRC    := src/colors.cc \
          src/cursor.cc \
          src/input.cc \
          src/panel.cc \
          src/integer.cc \
          src/console.cc \
          src/printer.cc \
          src/elements/element.cc

.PHONY: build

build: compile
	$(info [+] Building $(notdir $(TARGET)))
	$(AR) cr $(TARGET) $(BUILD)/obj/*.o

compile: install-headers
	$(info [+] Compiling sources)
	for file in $(SRC); do \
		$(CXX) -c $(CFLAGS) $$file -o "$(BUILD)/obj/$$(basename $${file%.*}).o"; \
	done

install-headers: prepare
	$(info [+] Installing headers)
	cp src/chars.h $(PREFIX)/include/cterm
	cp src/input.h $(PREFIX)/include/cterm
	cp src/panel.h $(PREFIX)/include/cterm
	cp src/colors.h $(PREFIX)/include/cterm
	cp src/cursor.h $(PREFIX)/include/cterm
	cp src/integer.h $(PREFIX)/include/cterm
	cp src/console.h $(PREFIX)/include/cterm
	cp src/printer.h $(PREFIX)/include/cterm
	cp src/elements/element.h $(PREFIX)/include/cterm/elements

prepare:
	$(info [+] Creating directories)
	mkdir -p $(BUILD)
	mkdir -p $(BUILD)/obj
	mkdir -p $(PREFIX)
	mkdir -p $(PREFIX)/bin
	mkdir -p $(PREFIX)/lib
	mkdir -p $(PREFIX)/include
	mkdir -p $(PREFIX)/include/cterm
	mkdir -p $(PREFIX)/include/cterm/elements

clean:
	$(info [+] Cleaning up)
	rm -rf $(BUILD)/obj

# TEMPRORARY
test: build
	$(info [+] Building test)
	$(CXX) $(CFLAGS) -L$(BUILD)/lib test.cc -lcterm -o $(BUILD)/bin/test

$(V).SILENT:
