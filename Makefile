# GNU makefile for libwebvtt

PACKAGE := webvtt

CFLAGS = -g -Wall

PROGS := test_webvtt
LIBRARIES := webvtt

webvtt_SRCS := webvtt.c
webvtt_HDRS := webvtt.h

test_webvtt_SRCS := test_webvtt.c libwebvtt.a

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

clean:
	$(RM) $(ALL_OBJS)
	$(RM) $(BUILD_LIBRARIES)
	$(RM) $(PROGS)

dist:
	@echo $@ target not implemented

distcheck: dist
	@echo $@ target not implemented

.PHONEY: all check clean dist distcheck

define library_template
 $(1)_OBJS := $$($(1)_SRCS:.c=.o)
 ALL_OBJS += $$($(1)_OBJS)
 lib$(1).a: $$($(1)_OBJS)
	$$(AR) cr $$@ $$^
	$$(RANLIB) $$@
endef

define program_template
 $(1)_OBJS := $$($(1)_SRCS:.c=.o)
 ALL_OBJS += $$($(1)_OBJS)
 $(1): $$($(1)_OBJS)
	$(CC) $$(LDFLAGS) -o $$@ $$^ $$($(1)_LIBS:%=-l%)
endef

$(foreach lib,$(LIBRARIES),$(eval $(call library_template,$(lib))))
$(foreach prog,$(PROGS),$(eval $(call program_template,$(prog))))

