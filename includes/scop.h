#ifndef SCOP_H
# define SCOP_H

# include <stdio.h>
# include <libft.h>
# include <OpenGl/gl3.h>
# include <mlx.h>
# include "../libsrcs/mlx/mlx_opengl.h"

typedef struct s_data {
	void	*mlx_ptr;
	void	*win;

	GLuint vertex_shader_id;
	GLuint fragment_shader_id;
	GLuint program_id;
	GLuint vao_id;
	GLuint vbo_id;
	GLuint color_buffer_id;
	const GLchar* vertex_shader;
	const GLchar* fragment_shader;
}					t_data;

#endif
