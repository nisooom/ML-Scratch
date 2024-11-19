# Compiler settings
CXX = g++
CXXFLAGS = -O3 -Wall
DEFINES  =
INCLUDES = -I . -I external/
LDFLAGS  = 

# Libraries (add your libraries here)
LIBS = 

# Target executable directory
OUT_DIR = out

# Directories
SRC_DIR = src
BUILD_DIR = build
EXAMPLE_DIR = examples

# Source files in src and example files in examples
SOURCES = $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
EXAMPLES = $(wildcard $(EXAMPLE_DIR)/*.cpp)

# Object files in build, maintaining directory structure for src files
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Executable names
TARGETS = $(patsubst $(EXAMPLE_DIR)/%.cpp, $(OUT_DIR)/%, $(EXAMPLES))

# Display sources, objects, and targets for debugging
$(info SOURCES: $(SOURCES))
$(info OBJECTS: $(OBJECTS))
$(info TARGETS: $(TARGETS))

# Default target to build all executables
all: $(TARGETS)

# Rule to compile source files into object files, maintaining subdirectory structure
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

# Rule to link the executables
$(OUT_DIR)/%: $(EXAMPLE_DIR)/%.cpp $(OBJECTS)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEFINES) $(INCLUDES) $(LDFLAGS) $(LIBS) -o $@ $< $(OBJECTS)

# Clean up object files and the target executables
clean:
	rm -rf $(BUILD_DIR) $(OUT_DIR)

# Rebuild the project from scratch
redo: clean all

.PHONY: all clean redo