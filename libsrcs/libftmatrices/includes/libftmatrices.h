#ifndef LIBFT_MATRICES_H
# define LIBFT_MATRICES_H
# include <libft.h>
# include <stdio.h>

typedef	int t_mat4x4[4][4]; // mat4x4[line][column]
typedef int	t_vec4[4];

void	ft_mat4x4_set_identity(t_mat4x4 matrice);
void	ft_mat4x4_print(t_mat4x4 matrice);
void	ft_mat4x4_mult(t_mat4x4 ret, t_mat4x4 m1, t_mat4x4 m2);
void	ft_mat4x4_copy(t_mat4x4 dest, t_mat4x4 src);
void	ft_mat4x4_mult_with_int(t_mat4x4 rez, t_mat4x4 m, int r);
void	ft_mat4x4_mult_with_vec4(t_vec4 rez, t_mat4x4 m1, t_vec4 vec);

void	ft_vec4_init(t_vec4 vec, int tab[4]);
void	ft_vec4_print(t_vec4 v);


#endif
