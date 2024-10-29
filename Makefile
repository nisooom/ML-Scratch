# Compiler settings
CXX = g++
CXXFLAGS = -O3 -Wno-narrowing
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

# Source files and corresponding object files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Default target to build the executable
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(DEFINES) $(INCLUDES) $(LDFLAGS) $(LIBS)

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(DEFINES) $(INCLUDES)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up object files and the target executable
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)

# Rebuild the project from scratch
redo: clean all

.PHONY: all clean redo