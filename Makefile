# Compiler settings
CXX = g++
CXXFLAGS = -O3 -Wall
DEFINES  = 
INCLUDES = -I . -I external/
LDFLAGS  = 

# Libraries (add your libraries here)
LIBS = 

# Target executable name
TARGET = app.exe

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files in src and main.cpp
SOURCES = $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp) main.cpp

# Object files in build, keeping directory structure for src files
OBJECTS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Display sources and objects for debugging
$(info SOURCES: $(SOURCES))
$(info OBJECTS: $(OBJECTS))

# Default target to build the executable
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(DEFINES) $(INCLUDES) $(LDFLAGS) $(LIBS)

# Rule to compile source files into object files, maintaining subdirectory structure
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)  # Automatically create necessary directories in build
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(DEFINES) $(INCLUDES)

# Clean up object files and the target executable
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Rebuild the project from scratch
redo: clean all

.PHONY: all clean redo
