SRC_NAME = main.c \
			shaders.c \
			keys_func_0.c \
			keys_func_1.c \
			keys_func_2.c \
			keys_func_3.c \
			keys_func_4.c \
			binary_tools.c \
			object.c \
			init_buffer.c \
			init.c \
			\
			obj_parser/main.c \
			obj_parser/handle_vertices.c \
			obj_parser/split_whitespace.c \
			obj_parser/tools.c \
			obj_parser/face.c \
			obj_parser/init.c \
			obj_parser/str_tools.c \
			obj_parser/line_tools.c \
			obj_parser/handles.c \
			obj_parser/fill.c \
			png/filter.c \
			png/filter_2.c \
			png/globals_inflate.c \
			png/huffman_get_code_from_length.c \
			png/inflate.c \
			png/inflate_2.c \
			png/parser.c \
			png/parser_2.c \
			png/parser_3.c \
			png/resize.c \
			png/tree.c

OBJ_PATH = ./obj/

INC_PATH = ./include ./libsrcs/libft/includes/ ./libsrcs/glfw-3.2.1/deps ./libsrcs/libftmatrices/includes

SRC_PATH = ./srcs/

NAME = scop

CC = gcc
CFLAGS =  -Wextra -Wall
LFLAGS = -lft -framework OpenGL -framework AppKit -lglfw -lftmatrices -lm 
LIB_DIR=./lib/

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
OBJ_NAME = $(SRC_NAME:.c=.o)

INC = $(addprefix -I,$(INC_PATH))

all : LIB_RULE GLFW $(NAME) $(NAME_CH)

GLFW_SRCS_PATH = libsrcs/glfw-3.2.1

$(LIB_DIR)libftmatrices.a:

LIB_RULE:
	@mkdir -p $(LIB_DIR)
	@make -C libsrcs/libftmatrices

GLFW: lib/libglfw.dylib

$(GLFW_SRCS_PATH):
	cd libsrcs && curl -OL 'https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip'
	unzip libsrcs/glfw-3.2.1.zip -d libsrcs
	rm libsrcs/glfw-3.2.1.zip

lib/libglfw.dylib: $(GLFW_SRCS_PATH)
	cd libsrcs/glfw-3.2.1 && cmake -DCMAKE_INSTALL_PREFIX:PATH=../../ -DBUILD_SHARED_LIBS=ON -DGLFW_USE_CHDIR=0 . && make && make install

$(NAME) : $(LIB_DIR)libftmatrices.a $(OBJ)
	make -C libsrcs/libft
	$(CC) $(CFLAGS) $(OBJ) -L $(LIB_DIR) $(LFLAGS) -o $@ 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -fv $(OBJ)
	@rmdir -p $(OBJ_PATH) 2> /dev/null || true
	@make -C libsrcs/libft clean
	@make -C libsrcs/libftmatrices clean
	@make -C libsrcs/glfw-3.2.1 clean || true

fclean: clean
	@rm -fv $(NAME)
	@make -C libsrcs/libft fclean
	@make -C libsrcs/libftmatrices fclean

fclean-dep: fclean
	@rm -rf include/GLFW
	@rm -rf lib/
	@mkdir -p lib/

re: fclean all

.PHONY : all clean fclean re GLFW LIB_RULE
