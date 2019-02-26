# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: magouin <magouin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 18:15:40 by magouin           #+#    #+#              #
#    Updated: 2017/12/19 20:03:53 by magouin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./

SRC_NAME = ft_mat4x4_set_identity.c \
			ft_mat4x4_set_zero.c \
			ft_mat4x4_set_projection.c \
			ft_mat4x4_set_translation.c \
			ft_mat4x4_set_rotation.c \
			ft_mat4x4_set_scale.c \
			ft_mat4x4_set_look_at.c \
			ft_mat4x4_print.c \
			ft_mat4x4_mult.c \
			ft_mat4x4_copy.c \
			ft_mat4x4_translate.c \
			ft_mat4x4_rotate.c \
			ft_mat4x4_scale.c \
			ft_mat4x4_translate_from_float_array.c \
			ft_mat4x4_rotate_from_float_array.c \
			ft_mat4x4_scale_from_float_array.c \
			ft_mat4x4_mult_with_real.c \
			ft_mat4x4_mult_with_vec4.c \
			ft_mat4x4_to_float_array.c \
			ft_vec4_init.c \
			ft_vec4_print.c \
			ft_vec4_to_vec3.c \
			ft_vec3_init.c \
			ft_vec3_dot.c \
			ft_vec3_print.c \
			ft_vec3_get_norme.c \
			ft_vec3_normalize.c \
			ft_vec3_sub.c \
			ft_vec3_add.c \
			ft_vec3_cross.c \
			ft_vec3_to_vec4.c \
			ft_vec3_scalar_mult.c \
			ft_vec3_rotate.c \
			ft_vec2_dot.c \
			ft_vec2_print.c \
			ft_vec2_get_norme.c \
			ft_vec2_normalize.c \
			ft_vec2_add.c \
			ft_vec2_dot.c \
			ft_vec2_sub.c \
			ft_vec2_get_normal.c

OBJ_PATH = ./obj/

INC_PATH = ./includes/ ../libft/includes

LIB_PATH = ./

NAME = ../../lib/libftmatrices.a

CC = gcc

CFLAGS = -Werror -Wall -Wextra -c -g
# CFLAGS = -Wall -Wextra -c -g

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
LIB = $(addprefix -L,$(LIB_PATH))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	ar r $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<


clean:
	/bin/rm -f $(OBJ)
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
