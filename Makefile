
NAME    = scop.exe
OBJ_DIR = obj
GLAD_DIR = libs/glad

SRC = src/main.cpp \
      src/VAO/VAO.cpp \
      src/VBO/VBO.cpp \
      src/EBO/EBO.cpp \
      src/shaders/shaderClass.cpp

OBJ = $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

GLAD_SRC = $(GLAD_DIR)/src/gl.c
GLAD_OBJ = $(OBJ_DIR)/gl.o
GLAD_HEADER = $(GLAD_DIR)/include/glad/gl.h
GLAD_KHR = $(GLAD_DIR)/include/KHR/khrplatform.h

CXX = g++
CC  = gcc

CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -I$(GLAD_DIR)/include -Isrc
CFLAGS   = -Wall -Wextra -Werror -I$(GLAD_DIR)/include
LDFLAGS  = -lglfw3 -lopengl32 -lgdi32

.PHONY: all clean fclean re run glad

all: $(NAME)

glad: $(GLAD_SRC) $(GLAD_HEADER) $(GLAD_KHR)

$(GLAD_SRC) $(GLAD_HEADER) $(GLAD_KHR) &: 
	python -m pip install glad2
	glad --api gl:core=3.3 --out-path $(GLAD_DIR) c

$(NAME): $(OBJ) $(GLAD_OBJ)
	$(CXX) $(OBJ) $(GLAD_OBJ) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: src/%.cpp $(GLAD_HEADER) $(GLAD_KHR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GLAD_OBJ): $(GLAD_SRC) $(GLAD_HEADER) $(GLAD_KHR)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(GLAD_SRC) -o $@

run: $(NAME)
	./$(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
