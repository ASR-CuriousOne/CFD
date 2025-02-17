OS := $(shell uname -s)

CXX = g++
SRC_DIR = src
BUILD_DIR = build
ifeq ($(OS), Windows_NT)  # Windows
    OUT_EXT := .exe
	CXXFLAGS = -Wall -Wextra -std=c++17 -g -MMD -MP
	LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

else  # Linux/macOS
	CXXFLAGS = -Wall -Wextra -std=c++17 -g -MMD -MP
	LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
    OUT_EXT :=
endif

BIN := App
BIN := $(BIN)$(OUT_EXT)

# Find all C++ source files
SRC = $(wildcard $(SRC_DIR)/*/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

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
