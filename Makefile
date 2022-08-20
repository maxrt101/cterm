
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
          src/value.cc \
          src/printer.cc \
          src/panel.cc \
          src/console.cc \
          src/layout.cc \
          src/widget.cc \
					src/widgets/*.cc

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
	cp src/*.h $(PREFIX)/include/cterm
	cp src/widgets/*.h $(PREFIX)/include/cterm/widgets

prepare:
	$(info [+] Creating directories)
	mkdir -p $(BUILD)
	mkdir -p $(BUILD)/obj
	mkdir -p $(PREFIX)
	mkdir -p $(PREFIX)/bin
	mkdir -p $(PREFIX)/lib
	mkdir -p $(PREFIX)/include
	mkdir -p $(PREFIX)/include/cterm
	mkdir -p $(PREFIX)/include/cterm/widgets

clean:
	$(info [+] Cleaning up)
	rm -rf $(BUILD)/obj

# TEMPRORARY
test: build
	$(info [+] Building test)
	$(CXX) $(CFLAGS) -L$(BUILD)/lib test.cc -lcterm -o $(BUILD)/bin/test

$(V).SILENT:
