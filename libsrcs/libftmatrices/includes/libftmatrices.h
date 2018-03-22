#ifndef LIBFT_MATRICES_H
# define LIBFT_MATRICES_H
# include <libft.h>
# include <stdio.h>
# include <math.h>

typedef	double t_mat4x4[4][4]; // mat4x4[line][column]
typedef double	t_vec4[4];
typedef double	t_vec3[3];

void	ft_mat4x4_set_identity(t_mat4x4 matrice);
void	ft_mat4x4_set_zero(t_mat4x4 m);
void	ft_mat4x4_set_projection(t_mat4x4 m, double array[4]);
void	ft_mat4x4_set_translation(t_mat4x4 m, t_vec3 v);

void	ft_mat4x4_print(t_mat4x4 matrice);
void	ft_mat4x4_mult(t_mat4x4 ret, t_mat4x4 m1, t_mat4x4 m2);
void	ft_mat4x4_copy(t_mat4x4 dest, t_mat4x4 src);
void	ft_mat4x4_mult_with_int(t_mat4x4 rez, t_mat4x4 m, int r);
void	ft_mat4x4_mult_with_vec4(t_vec4 rez, t_mat4x4 m1, t_vec4 vec);

void    ft_mat4x4_to_float_array(float dest[16], t_mat4x4 matrice);

void	ft_vec4_init(t_vec4 vec, double tab[4]);
void	ft_vec4_print(t_vec4 v);

void	ft_vec3_init(t_vec3 vec, double tab[3]);
void	ft_vec3_print(t_vec3 v);


#endif
