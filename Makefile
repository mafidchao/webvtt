# GNU makefile for libwebvtt

# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

PACKAGE := webvtt

# Tools
lc = $(subst A,a,$(subst B,b,$(subst C,c,$(subst D,d,$(subst E,e,$(subst F,f,$(subst G,g,$(subst H,h,$(subst I,i,$(subst J,j,$(subst K,k,$(subst L,l,$(subst M,m,$(subst N,n,$(subst O,o,$(subst P,p,$(subst Q,q,$(subst R,r,$(subst S,s,$(subst T,t,$(subst U,u,$(subst V,v,$(subst W,w,$(subst X,x,$(subst Y,y,$(subst Z,z,$1))))))))))))))))))))))))))

# Configuration
OS := $(call lc,$(shell uname -r))
ARCH := $(call lc,$(shell uname -m))
CONFIG := development
BUILDNAME := $(CONFIG)-$(OS)-$(ARCH)

# Platform suffixes
A := .a
O := .o
SA := .sa
EXE := .exe

# Source tree
ROOT := ./
RBIN := $(ROOT)bin/
BIN := $(RBIN)$(BUILDNAME)/
SRC := $(ROOT)src/
INCLUDE := $(ROOT)include/
TEST := $(ROOT)test/
SPEC := $(TEST)spec/
VTT := $(TEST)vtt/
ROBJ := $(ROOT)obj/
OBJ := $(ROBJ)$(BUILDNAME)/
RLIB := $(ROOT)lib/
LIB := $(RLIB)$(BUILDNAME)/

# GCC
CC := gcc
PYTHON = python
CFLAGS = -I$(INCLUDE) -g -Wall
LDFLAGS := -L$(LIB)

# Targets
LIBRARIES := libwebvtt
PROGRAMS := parsevtt
TARGETS := $(LIBRARIES) $(PROGRAMS)
EXTRA_DIST := LICENSE README.md
COMMON_DIRS := $(RLIB) $(LIB) $(ROBJ) $(OBJ) $(RBIN) $(BIN)

# Test stuff
TESTS := $(shell find $(TEST) -name '*.test' -print)
VTTS := $(patsubst $(SPEC)%.test,$(VTT)%.vtt,$(TESTS))
STIPVTT = $(SPEC)/strip-vtt.py

## below this point is boilerplate

BUILD_LIBRARIES := $(LIBRARIES:%=$(LIB)%$(A))
BUILD_PROGRAMS := $(PROGRAMS:%=$(BIN)%$(EXE))
# so that linking parsevtt uses flags -lwebvtt
parsevtt_LIBS := webvtt
RANLIB ?= ranlib

# templates generate per-target rules
define make_intermittent_targets
$(1)_SRCS := $$(shell find $$(SRC)$(1) -name "*.c")
$(1)_OBJS := $$(patsubst $$(SRC)$(1)/%.c,$$(OBJ)$(1)/%$(O),$$($(1)_SRCS))
$(1)_OBJS: $$(shell find $$(SRC)$(1) -name "*.h")
ALL_OBJS += $$($(1)_OBJS)
endef

define library_template
$(1)_DIRS := $$(sort $$(dir $$($(1)_OBJS)))
.PHONY: $$($(1)_DIRS)
$$($(1)_DIRS):
	@-mkdir -p $$@ 2>/dev/null
$$($(1)_OBJS): $$(COMMON_DIRS) $$($(1)_DIRS)
$(LIB)$(1)$(A): $$($(1)_OBJS) | $$(COMMON_DIRS) $$($(1)_DIRS)
	$$(AR) cr $$@ $$^
	$$(RANLIB) $$@
endef

define program_template
$(1)_DIRS := $$(sort $$(dir $$($(1)_OBJS)))
.PHONY: $$($(1)_DIRS)
$$($(1)_DIRS):
	@-mkdir -p $$@ 2>/dev/null
$$($(1)_OBJS): $$(COMMON_DIRS) $$($(1)_DIRS)
$(BIN)$(1)$(EXE): $$($(1)_OBJS) | $$(COMMON_DIRS) $$($(1)_DIRS)
	$(CC) $$(LDFLAGS) -o $$@ $$^ $$($(1)_LIBS:%=-l%)
endef

all: $(BUILD_LIBRARIES) $(BUILD_PROGRAMS) | $(COMMON_DIRS)

$(COMMON_DIRS):
	@-mkdir -p $@ 2>/dev/null

libwebvtt: $(LIB)libwebvtt$(A)
parsevtt: $(BIN)parsevtt$(EXE)

$(foreach T,$(TARGETS),$(eval $(call make_intermittent_targets,$(T)))) 
$(foreach T,$(LIBRARIES),$(eval $(call library_template,$(T))))
$(foreach T,$(PROGRAMS),$(eval $(call program_template,$(T))))

check: $(BIN)parsevtt$(EXE) $(VTTS)
	$(PYTHON) $(SPEC)webvtt-conformance-test.py $(BIN)parsevtt$(EXE) $(VTT)

check-js: $(VTTS)
	$(PYTHON) $(SPEC)webvtt-conformance-test.py $(VTT)

$(VTT)%.vtt : $(SPEC)%.test
	@$(PYTHON) $(STIPVTT) $< $@

$(OBJ)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(ALL_OBJS)
	$(RM) -fr $(OBJ)
	$(RM) $(BUILD_LIBRARIES)
	$(RM) $(BUILD_PROGRAMS)

VERSION ?= $(firstword $(git describe --tags) dev)

dist: $(PACKAGE)-$(VERSION).tar.gz
	@echo $(ALL_SRCS)

$(PACKAGE)-$(VERSION).tar.gz: Makefile $(SRC) $(INCLUDE) $(EXTRA_DIST)
	-$(RM) -r $(PACKAGE)-$(VERSION)
	mkdir -p $(PACKAGE)-$(VERSION)
	cp -r $^ $(PACKAGE)-$(VERSION)/
	tar cvzf $(PACKAGE)-$(VERSION).tar.gz $(PACKAGE)-$(VERSION)/
	$(RM) -r $(PACKAGE)-$(VERSION)

distcheck: dist
	tar xvf $(PACKAGE)-$(VERSION).tar.gz
	make -C $(PACKAGE)-$(VERSION) check
	$(RM) -r $(PACKAGE)-$(VERSION)
	@echo $(PACKAGE)-$(VERSION).tar.gz ready to distribute

.PHONEY: all libwebvtt parsevtt check clean dist distcheck
