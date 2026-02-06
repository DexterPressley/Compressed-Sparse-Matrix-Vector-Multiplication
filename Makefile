TARGET := matrix-multiplication
SRC_DIRS := ./src
TARGET_FLAGS :=  
# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' )

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CXXFLAGS := -std=c++20 -Wall -Wextra -O2

BUILD_DIR := ./build
RELEASE_DIR = $(BUILD_DIR)/release

.PHONY: all debug1 debug2 clean whatever...
clean:
	rm -r $(BUILD_DIR)

OBJS := $(SRCS:%=$(BUILD_DIR)/.*/%.o)
DEPS := $(OBJS:.o=.d)

RELEASE_OBJS := $(SRCS:%=$(RELEASE_DIR)/%.o)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)

# Commands

run: $(RELEASE_DIR)/$(TARGET)
	./$(RELEASE_DIR)/$(TARGET) $(TARGET_FLAGS)

compile: $(RELEASE_DIR)/$(TARGET) 

# The final build step.
$(RELEASE_DIR)/$(TARGET): $(RELEASE_OBJS)
	$(CXX) $(RELEASE_OBJS) -o $@ $(LDFLAGS)

# Build step for C++ source
$(RELEASE_DIR)/%.cpp.o: %.cpp
	mkdir -p $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	