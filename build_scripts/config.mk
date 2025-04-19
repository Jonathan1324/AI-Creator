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

# files
C_SRCS := $(wildcard $(SRC_DIR)/*.c)
C_SRCS += $(wildcard $(SRC_DIR)/*/*.c)
C_SRCS += $(wildcard $(SRC_DIR)/*/*/*.c)
C_SRCS += $(wildcard $(SRC_DIR)/*/*/*/*.c)
C_SRCS += $(wildcard $(SRC_DIR)/*/*/*/*/*.c)
C_HEADERS := $(wildcard $(SRC_DIR)/*.h)
C_HEADERS += $(wildcard $(SRC_DIR)/*/*.h)
C_HEADERS += $(wildcard $(SRC_DIR)/*/*/*.h)
C_HEADERS += $(wildcard $(SRC_DIR)/*/*/*/*.h)
C_HEADERS += $(wildcard $(SRC_DIR)/*/*/*/*/*.h)

CPP_SRCS := $(wildcard $(SRC_DIR)/*.cpp)
CPP_SRCS += $(wildcard $(SRC_DIR)/*/*.cpp)
CPP_SRCS += $(wildcard $(SRC_DIR)/*/*/*.cpp)
CPP_SRCS += $(wildcard $(SRC_DIR)/*/*/*/*.cpp)
CPP_SRCS += $(wildcard $(SRC_DIR)/*/*/*/*/*.cpp)
CPP_HEADERS := $(wildcard $(SRC_DIR)/*.hpp)
CPP_HEADERS += $(wildcard $(SRC_DIR)/*/*.hpp)
CPP_HEADERS += $(wildcard $(SRC_DIR)/*/*/*.hpp)
CPP_HEADERS += $(wildcard $(SRC_DIR)/*/*/*/*.hpp)
CPP_HEADERS += $(wildcard $(SRC_DIR)/*/*/*/*/*.hpp)