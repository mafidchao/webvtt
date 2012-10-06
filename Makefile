# GNU makefile for libwebvtt

# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

PACKAGE := webvtt

CFLAGS = -g -Wall

PROGS := test_webvtt
LIBRARIES := webvtt

webvtt_SRCS := webvtt.c
webvtt_HDRS := webvtt.h

test_webvtt_SRCS := test_webvtt.c libwebvtt.a

EXTRA_DIST := LICENSE

PYTHON = python

SRC_DIR = .
TEST_DIR = $(SRC_DIR)/test
SPEC_DIR = $(TEST_DIR)/spec
OBJ_DIR = $(SRC_DIR)/objdir
OBJ_DIR_SPEC = $(OBJ_DIR)/test/spec
# Get all the .test files underneath the directory specified by $(SPEC_DIR)
TEST_SRC := $(shell find $(SPEC_DIR) -name '*.test' -print)
# Transform all .test files rooted in ./test to .vtt rooted in
# .objdir/test
VTT_SRC := $(subst $(SRC_DIR)/test,$(OBJ_DIR)/test,$(subst .test,.vtt,$(TEST_SRC)))

STIP_VTT = $(SPEC_DIR)/strip-vtt.py

## below this point is boilerplate

BUILD_LIBRARIES := $(LIBRARIES:%=lib%.a)
RANLIB ?= ranlib

all: $(PROGS) $(BUILD_LIBRARIES)

check: all
	@for prog in $(PROGS); do \
	  if ! ./$$prog; then       \
	    echo ./$$prog  FAIL;  \
	  else \
	    echo ./$$prog  ok;    \
	  fi; \
	done

objdir:
	mkdir $(OBJ_DIR)

check-js: objdir $(VTT_SRC)
	$(PYTHON) ./test/spec/run-tests-js.py $(OBJ_DIR_SPEC)

$(OBJ_DIR)/%.vtt : $(SRC_DIR)/%.test
	@$(PYTHON) $(STIP_VTT) $< $@

clean:
	$(RM) $(ALL_OBJS)
	$(RM) -fr $(OBJ_DIR)
	$(RM) $(BUILD_LIBRARIES)
	$(RM) $(PROGS)

# templates generate per-target rules
define library_template
 $(1)_OBJS := $$($(1)_SRCS:.c=.o)
 $(1)_OBJS : $$($(1)_HDRS)
 ALL_OBJS += $$($(1)_OBJS)
 ALL_SRCS += $$(filter-out .a,$$($(1)_SRCS) $$($(1)_HDRS))
 lib$(1).a: $$($(1)_OBJS)
	$$(AR) cr $$@ $$^
	$$(RANLIB) $$@
endef

define program_template
 $(1)_OBJS := $$($(1)_SRCS:.c=.o)
 $(1)_OBJS : $$($(1)_HDRS)
 ALL_OBJS += $$($(1)_OBJS)
 ALL_SRCS += $$(filter-out %.a,$$($(1)_SRCS) $$($(1)_HDRS))
 $(1): $$($(1)_OBJS)
	$(CC) $$(LDFLAGS) -o $$@ $$^ $$($(1)_LIBS:%=-l%)
endef

$(foreach lib,$(LIBRARIES),$(eval $(call library_template,$(lib))))
$(foreach prog,$(PROGS),$(eval $(call program_template,$(prog))))

VERSION ?= $(firstword $(git describe --tags) dev)

dist: $(PACKAGE)-$(VERSION).tar.gz
	@echo $(ALL_SRCS)

$(PACKAGE)-$(VERSION).tar.gz: Makefile $(ALL_SRCS) $(EXTRA_DIST)
	-$(RM) -r $(PACKAGE)-$(VERSION)
	mkdir $(PACKAGE)-$(VERSION)
	cp $^ $(PACKAGE)-$(VERSION)/
	tar cvzf $(PACKAGE)-$(VERSION).tar.gz $(PACKAGE)-$(VERSION)/
	$(RM) -r $(PACKAGE)-$(VERSION)

distcheck: dist
	tar xvf $(PACKAGE)-$(VERSION).tar.gz
	make -C $(PACKAGE)-$(VERSION) check
	$(RM) -r $(PACKAGE)-$(VERSION)
	@echo $(PACKAGE)-$(VERSION).tar.gz ready to distribute

.PHONEY: all check clean dist distcheck
