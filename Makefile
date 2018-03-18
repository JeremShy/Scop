SRC_NAME = main.c \
			shaders.c

OBJ_PATH = ./obj/

INC_PATH = ./include ./libsrcs/libft/includes/ ./libsrcs/glfw-3.2.1/deps

SRC_PATH = ./srcs/

NAME = scop

CC = gcc
CFLAGS =  -Wextra -Wall -g
LFLAGS = -lft -framework OpenGL -framework AppKit -lglfw
LIB_DIR=./lib/

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
OBJ_NAME = $(SRC_NAME:.c=.o)

INC = $(addprefix -I,$(INC_PATH))

all : LIB_RULE GLFW $(NAME) $(NAME_CH)

GLFW_SRCS_PATH = libsrcs/glfw-3.2.1

LIB_RULE:
	@mkdir -p $(LIB_DIR)

GLFW: lib/libglfw.dylib

$(GLFW_SRCS_PATH):
	cd libsrcs && curl -OL 'https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip'
	unzip libsrcs/glfw-3.2.1.zip -d libsrcs
	rm libsrcs/glfw-3.2.1.zip

lib/libglfw.dylib: $(GLFW_SRCS_PATH)
	cd libsrcs/glfw-3.2.1 && cmake -DCMAKE_INSTALL_PREFIX:PATH=../../ -DBUILD_SHARED_LIBS=ON -DGLFW_USE_CHDIR=0 . && make && make install

$(NAME) : $(OBJ)
	make -C libsrcs/libft
#	make -C libsrcs/mlx
	$(CC) $(CFLAGS) $(OBJ) -L $(LIB_DIR) $(LFLAGS) -o $@ 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -fv $(OBJ)
	@rmdir -p $(OBJ_PATH) 2> /dev/null || true
	@make -C libsrcs/libft clean
#	@make -C libsrcs/mlx clean
	@make -C libsrcs/glfw-3.2.1 clean

fclean: clean
	@rm -fv $(NAME)
#	@make -C libsrcs/mlx fclean
	@make -C libsrcs/libft fclean

fclean-dep: fclean
	@rm -rf include/GLFW
	@rm -rf lib/
	@mkdir -p lib/

re: fclean all

.PHONY : all clean fclean re GLFW
