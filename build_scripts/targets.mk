OBJS := $(C_SRCS:$(SRC_DIR)/%.c=$(DEBUG_DIR)/c/%.o) $(CPP_SRCS:$(SRC_DIR)/%.cpp=$(DEBUG_DIR)/cpp/%.o)

PREBUILD = preBuild$(EXE_EXT)
RELEASE = $(RELEASE_DIR)/main$(EXE_EXT)

.PHONY: all clean

all: $(PREBUILD) $(RELEASE)

clean:
	@$(RMDIR) debug
	@$(RMDIR) release
	@-$(RMDIR) $(PREBUILD)