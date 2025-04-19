OBJS := $(C_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/c/%.o) $(CPP_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/cpp/%.o)

DEBUG = $(DEBUG_DIR)/main$(EXE_EXT)
RELEASE = $(RELEASE_DIR)/main$(EXE_EXT)

.PHONY: all clean

all: $(DEBUG) $(RELEASE)

clean:
	@$(RMDIR) $(BUILD_DIR)
	@$(RMDIR) $(RELEASE_DIR)
	@$(RMDIR) $(DEBUG_DIR)
	@-$(RMDIR) $(DEBUG)