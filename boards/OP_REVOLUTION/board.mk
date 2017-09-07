# Required include directories
ifeq ($(BOARDINC),)
  BOARDINC := $(dir $(lastword $(MAKEFILE_LIST)))
endif

# List of all the board related files.
BOARDSRC = $(BOARDINC)board.c
