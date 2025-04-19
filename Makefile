include build_scripts/config.mk
include build_scripts/os-specific.mk
include build_scripts/targets.mk


$(DEBUG_DIR)/c/%.o: $(SRC_DIR)/%.c $(C_HEADERS)
	@$(MKDIR) $(DEBUG_DIR)
	@$(MKDIR) $(DEBUG_DIR)/c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled c files"

$(DEBUG_DIR)/cpp/%.o: $(SRC_DIR)/%.cpp $(CPP_HEADERS)
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
