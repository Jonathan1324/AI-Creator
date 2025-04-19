# compiler and flags
CC = gcc
CXX = g++

CFLAGS = -Wall -g -Iinclude
CXXFLAGS = -Wall -g -Iinclude

RELEASE_CFLAGS = -Wall -O2 -Iinclude
RELEASE_LDFLAGS = -s

# directories
SRC_DIR = src
BUILD_DIR = build

DEBUG_DIR = debug
RELEASE_DIR = release

define recurse-C_SRCS
  $(wildcard $(1)/*.c) \
  $(foreach dir,$(wildcard $(1)/*),$(call recurse-C_SRCS,$(dir)))
endef

define recurse-C_HEADERS
  $(wildcard $(1)/*.h) \
  $(foreach dir,$(wildcard $(1)/*),$(call recurse-C_HEADERS,$(dir)))
endef

define recurse-CPP_SRCS
  $(wildcard $(1)/*.cpp) \
  $(foreach dir,$(wildcard $(1)/*),$(call recurse-CPP_SRCS,$(dir)))
endef

define recurse-CPP_HEADERS
  $(wildcard $(1)/*.hpp) \
  $(foreach dir,$(wildcard $(1)/*),$(call recurse-CPP_HEADERS,$(dir)))
endef

# files
C_SRCS := $(call recurse-C_SRCS,$(SRC_DIR))
C_HEADERS := $(call recurse-C_HEADERS,$(SRC_DIR))

CPP_SRCS := $(call recurse-CPP_SRCS,$(SRC_DIR))
CPP_HEADERS := $(call recurse-CPP_HEADERS,$(SRC_DIR))