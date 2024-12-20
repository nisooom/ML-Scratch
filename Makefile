# Compiler settings
CXX      = g++
CXXFLAGS = -O3 -Wall 
DEFINES  = 
INCLUDES = -I . -I external/
LDFLAGS  = 

# Libraries (add your libraries here)
LIBS = 

# Target executable directory
OUT_DIR = out

# Directories
SRC_DIR     = src
BUILD_DIR   = build
EXAMPLE_DIR = examples

# Source files in src and example files in examples
SOURCES  = $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
EXAMPLES = $(wildcard $(EXAMPLE_DIR)/*.cpp)

# Object files in build, keeping directory structure for src files
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Executable names
TARGETS = $(patsubst $(EXAMPLE_DIR)/%.cpp, $(OUT_DIR)/%, $(EXAMPLES))


# Default target to build all executables


# Rule to link the executables
$(OUT_DIR)/%: $(EXAMPLE_DIR)/%.cpp $(OBJECTS)
	mkdir -p $(dir $@)
	$(CXX) -o $@ $< $(OBJECTS) $(CXXFLAGS) $(DEFINES) $(INCLUDES) $(LDFLAGS) $(LIBS)

# Rule to compile source files into object files, maintaining subdirectory structure
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(DEFINES) $(INCLUDES)

# Clean up object files and the target executables
clean:
	rm -rf $(OUT_DIR)/*

# Rebuild the project from scratch
redo: clean all

.PHONY: all clean 