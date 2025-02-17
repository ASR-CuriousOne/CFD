CXX = g++
SRC_DIR = src
BUILD_DIR = build

VULKAN_SDK := C:/VulkanSDK/1.4.304.0# Change this to your Vulkan SDK path
GLFW_DIR := C:/glfw/glfw-3.4.bin.WIN64

ifeq ($(OS), Windows_NT)  # Windows
    OUT_EXT := .exe
	CXXFLAGS = -Wall -Wextra -std=c++17 -g -MMD -MP 
	LDFLAGS := 
	INCLUDE_DIRS := -I $(VULKAN_SDK)/Include -I $(GLFW_DIR)/include
	LIB_DIRS := -L $(VULKAN_SDK)/Lib -L $(GLFW_DIR)/lib
	LIBS := -lvulkan-1 "$(GLFW_DIR)/lib-mingw-w64/libglfw3.a" -lgdi32	

else  # Linux/macOS
	CXXFLAGS = -Wall -Wextra -std=c++17 -g -MMD -MP
	LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
	INCLUDE_DIRS :=
	LIB_DIRS := 
	LIBS :=
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
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LIB_DIRS) $(LIBS)

# Compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@ 
	
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
