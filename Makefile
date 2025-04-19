ifeq ($(OS),Windows_NT)
	RMDIR = rmdir /S /Q
	MKDIR = if not exist
	NULLDEV = nul

	LDFLAGS = -static

	EXE_EXT = .exe
else
	RMDIR = rm -rf
	MKDIR = mkdir -p
	NULLDEV = /dev/null

	ifeq ($(UNAME_S),Linux)
		LDFLAGS = -static
	else
		LDFLAGS =
	endif

	EXE_EXT =
endif

# compiler and flags
CC = gcc
CXX = g++

CFLAGS = -Wall -g -Iinclude
CXXFLAGS = -Wall -g -Iinclude

RELEASE_CFLAGS = -Wall -O2 -Iinclude
RELEASE_LDFLAGS = -s


# directories
SRC_DIR = src
DEBUG_DIR = debug
RELEASE_DIR = release

# files
C_SRCS := $(wildcard $(SRC_DIR)/*.c)
CPP_SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(C_SRCS:$(SRC_DIR)/%.c=$(DEBUG_DIR)/c/%.o) $(CPP_SRCS:$(SRC_DIR)/%.cpp=$(DEBUG_DIR)/cpp/%.o)

# targets
PREBUILD = preBuild$(EXE_EXT)
RELEASE = $(RELEASE_DIR)/main$(EXE_EXT)

.PHONY: all clean

# default target
all: $(PREBUILD) $(RELEASE)


$(DEBUG_DIR)/c/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(DEBUG_DIR)
	@$(MKDIR) $(DEBUG_DIR)/c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled c files"

$(DEBUG_DIR)/cpp/%.o: $(SRC_DIR)/%.cpp
	@$(MKDIR) $(DEBUG_DIR)
	@$(MKDIR) $(DEBUG_DIR)/cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled c++ files"


$(PREBUILD): $(OBJS)
	@$(CXX) $(OBJS) $(LDFLAGS) -o $@
	@echo "Created preBuild"


$(RELEASE): $(OBJS)
	@$(MKDIR) $(RELEASE_DIR)
	@$(CXX) $(OBJS) $(LDFLAGS) $(RELEASE_LDFLAGS) -O2 -o $@
	@echo "Created release file"

clean:
	@$(RMDIR) debug
	@$(RMDIR) release
	@-$(RMDIR) $(PREBUILD)
