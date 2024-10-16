CXX = g++
CXXFLAGS = -Wall -std=c++11
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = build
TARGET = $(OBJ_DIR)/inventario

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)  # Crear el directorio de compilación si no existe
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

run: all
	./$(TARGET)