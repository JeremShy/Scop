#include <scop.h>
#include <sys/stat.h>
#include <fcntl.h>
int8_t	check_compilation(GLuint shader, const char *filename)
{
	GLsizei i;
	GLchar buffer[1024];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &i);
	if (i == GL_TRUE)
		return (shader);
	glGetShaderInfoLog(shader, 1024, &i, buffer);
	printf("COMPILATION ERROR  [%s] : \n%s\n", filename, buffer);
	return (0);
}

static GLuint close_and_return(int fd, GLuint ret)
{
	close(fd);
	return (ret);
}

GLuint	create_and_compile_shader(const char *filename, GLenum shaderType) //Returns 0 on error
{
	GLuint		ret;
	int			fd;
	struct stat	buf;
	GLchar		*file_content;
	int			r;
	GLint		length;

	ret = glCreateShader(shaderType);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	if (fstat(fd, &buf) == -1)
		return (close_and_return(fd, 0));
	if (!(file_content = malloc(sizeof(GLchar) * (buf.st_size + 1))))
		return (close_and_return(fd, 0));
	if ((r = read(fd, file_content, buf.st_size + 1)) != buf.st_size)
	{
		free(file_content);
		return (close_and_return(fd, 0));
	}
	file_content[r] = '\0';
	length = buf.st_size;
	glShaderSource(ret, 1, (const GLchar *const *)&file_content, &length);
	free(file_content);
	close(fd);
	glCompileShader(ret);
	return (check_compilation(ret, filename));
}

GLuint create_and_link_program(GLuint vertex_sh, GLuint fragment_sh)
{
	GLuint	ret;
	GLint	i;
	int		success;
	GLchar buffer[1024];

	ret = glCreateProgram();
	glAttachShader(ret, vertex_sh);
	glAttachShader(ret, fragment_sh);
	glLinkProgram(ret);

	glGetProgramiv(ret, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(ret, 1024, NULL, buffer);
		printf("Error while linking : %s\n", buffer);
	}
	glDeleteShader(vertex_sh);
	glDeleteShader(fragment_sh);

	glGetProgramiv(ret, GL_LINK_STATUS, &i);
	if (i != GL_TRUE)
		return (0);
	return (ret);
}
