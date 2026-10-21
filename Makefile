NAME    = scop
SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

GLAD_SRC = libs/glad/src/gl.c
GLAD_OBJ = $(OBJ_DIR)/gl.o

CXX      = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -Ilibs/glad/include
LDFLAGS  = -lglfw3 -lopengl32 -lgdi32

all: $(NAME)

$(NAME): $(OBJ) $(GLAD_OBJ)
	$(CXX) $(OBJ) $(GLAD_OBJ) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GLAD_OBJ): $(GLAD_SRC)
	mkdir -p $(OBJ_DIR)
	gcc -c $< -Ilibs/glad/include -o $@

run:
	./scop.exe

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re