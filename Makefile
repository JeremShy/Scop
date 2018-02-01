SRC_NAME = main.c

OBJ_PATH = ./obj/

INC_PATH = ./includes ./libsrcs/libft/includes/

SRC_PATH = ./srcs/

NAME = scop

CC = gcc
CFLAGS =  -Wextra -Wall -g
LFLAGS = -lft -lmlx -framework OpenGL -framework AppKit
LIB_DIR=./lib/

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
OBJ_NAME = $(SRC_NAME:.c=.o)

INC = $(addprefix -I,$(INC_PATH))

all : LIB_RULE $(NAME) $(NAME_CH)

$(LCP_NAME) :

LIB_RULE:
	@mkdir -p $(LIB_DIR)

$(NAME) : $(OBJ)
	make -C libsrcs/libft
	make -C libsrcs/mlx
	$(CC) $(CFLAGS) $(OBJ) -L $(LIB_DIR) $(LFLAGS) -o $@ 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -fv $(OBJ)
	@rmdir -p $(OBJ_PATH) 2> /dev/null || true
	@make -C libsrcs/libft clean
	@make -C libsrcs/mlx clean

fclean: clean
	@rm -fv $(NAME)
	@rmdir lib 2> /dev/null || true
	@make -C libsrcs/mlx fclean
	@make -C libsrcs/libft fclean


re: fclean all

.PHONY : all clean fclean re
