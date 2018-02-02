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
	GLuint VertexArrayID;
	GLuint vertexbuffer;

}					t_data;

#endif
