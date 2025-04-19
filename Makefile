include build_scripts/os-specific.mk
include build_scripts/config.mk
include build_scripts/targets.mk


$(BUILD_DIR)/c/%.o: $(SRC_DIR)/%.c $(C_HEADERS)
	@$(MKDIR) $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled c files"

$(BUILD_DIR)/cpp/%.o: $(SRC_DIR)/%.cpp $(CPP_HEADERS)
	@$(MKDIR) $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled c++ files"


$(DEBUG): $(OBJS)
	@$(MKDIR) $(DEBUG_DIR)
	@$(CXX) $(OBJS) $(LDFLAGS) -o $@
	@echo "Created debug file"


$(RELEASE): $(OBJS)
	@$(MKDIR) $(RELEASE_DIR)
	@$(CXX) $(OBJS) $(LDFLAGS) $(RELEASE_LDFLAGS) -O2 -o $@
	@echo "Created release file"
