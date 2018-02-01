#include <stdio.h>
#include <libft.h>
#include <OpenGl/gl.h>
#include <OpenGl/glu.h>
#include <mlx.h>
#include "../libsrcs/mlx/mlx_opengl.h"

void	*mlx;
void	*window;

int	hook(void *window_local)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
		glColor3ub(0,0,255);
		glVertex2d(-0.75,-0.75);
		glVertex2d(-0.75,0.75);
		glColor3ub(255,0,0);
		glVertex2d(0.75,0.75);
		glVertex2d(0.75,-0.75);
	glEnd();

	mlx_opengl_swap_buffers(window_local);
}

int main()
{

	mlx = mlx_init();
	window = mlx_new_opengl_window(mlx, 640,480, "coucou");
	mlx_opengl_window_set_context(window);

	mlx_loop_hook(mlx, hook, window);
	mlx_loop (mlx);
	return (0);
}
