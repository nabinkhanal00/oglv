SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
INCLUDE_FLAGS := -I$(INCLUDE_DIR) -Ilib/glad -Ilib/imgui -Ilib/oglm
CC := g++
CFLAGS := -lglfw -lGL

EXECUTABLE := main

SOURCES :=  $(wildcard $(SRC_DIR)/*.cpp)  

IMGUI := $(wildcard lib/imgui/*.cpp)
GLAD := lib/glad/glad.cpp

OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o, $(SOURCES)) 
OBJECTS += $(patsubst lib/imgui/%.cpp,$(BUILD_DIR)/%.o, $(IMGUI)) 
OBJECTS += build/glad.o

build:$(EXECUTABLE)

run: 
	$(BUILD_DIR)/$(EXECUTABLE) 

$(EXECUTABLE):$(OBJECTS)
	$(CC) $(OBJECTS)  $(INCLUDE_FLAGS) -o $(BUILD_DIR)/$(EXECUTABLE)  $(CFLAGS)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC)  $(INCLUDE_FLAGS) -c $< -o $@  $(CFLAGS)


$(BUILD_DIR)/%.o : lib/imgui/%.cpp
	$(CC)  $(INCLUDE_FLAGS) -c $< -o $@  $(CFLAGS)

$(BUILD_DIR)/%.o : lib/glad/%.cpp
	$(CC)  $(INCLUDE_FLAGS) -c $< -o $@  $(CFLAGS)

clean:
	rm -r $(BUILD_DIR)/*
