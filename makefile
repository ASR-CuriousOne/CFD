
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g -MMD -MP
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
SRC_DIR = src
BUILD_DIR = build
BIN = App

# Find all C++ source files
SRC = $(wildcard $(SRC_DIR)/*/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

SRC_VERTS = $(wildcard $(SRC_DIR)/shaders/*.vert)
OBJ_VERTS = $(patsubst $(SRC_DIR)/%.vert, $(BUILD_DIR)/%.spv, $(SRC_VERTS))
SRC_FRAGS = $(wildcard $(SRC_DIR)/shaders/*.frag)
OBJ_FRAGS = $(patsubst $(SRC_DIR)/%.frag, $(BUILD_DIR)/%.spv, $(SRC_FRAGS))
# Default target
all: $(BIN)

# Build executable
$(BIN): $(OBJ) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
# Create build directory if not exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/app $(BUILD_DIR)/core $(BUILD_DIR)/renderer $(BUILD_DIR)/shaders

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

# Run application
run: all
	./$(BIN)

.PHONY: all clean run
