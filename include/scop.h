#ifndef SCOP_H
# define SCOP_H

# include <stdio.h>
# include <libft.h>
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

typedef struct s_d {
	GLFWwindow	*window;
	float		*vertices;

	GLuint	vertex_sh;
	GLuint	fragment_sh;
	GLuint	program;
}					t_d;

GLuint	create_and_compile_shader(const char *filename, GLenum shaderType);
GLuint create_and_link_program(GLuint vertex_sh, GLuint fragment_sh);

#endif
