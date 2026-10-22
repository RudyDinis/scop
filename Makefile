
NAME    = scop.exe
OBJ_DIR = obj

SRC = src/main.cpp \
      src/VAO/VAO.cpp \
      src/VBO/VBO.cpp \
      src/EBO/EBO.cpp \
      src/shaders/shaderClass.cpp

OBJ = $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

GLAD_SRC = libs/glad/src/gl.c
GLAD_OBJ = $(OBJ_DIR)/gl.o

CXX      = g++
CC       = gcc

CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -Ilibs/glad/include -Isrc
CFLAGS   = -Wall -Wextra -Werror -Ilibs/glad/include
LDFLAGS  = -lglfw3 -lopengl32 -lgdi32

.PHONY: all clean fclean re run

all: $(NAME)

$(NAME): $(OBJ) $(GLAD_OBJ)
	$(CXX) $(OBJ) $(GLAD_OBJ) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GLAD_OBJ): $(GLAD_SRC)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(NAME)
	./$(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
