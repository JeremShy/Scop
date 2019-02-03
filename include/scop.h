#ifndef SCOP_H
# define SCOP_H

# include <stdio.h>
# include <libft.h>
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <libftmatrices.h>

# include <sys/mman.h>

# define MAX_VERTICES_NBR 8192
# define MAX_OBJECTS_NBR 16
# define MAX_VERTICES_FACE 16

#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))


typedef struct	s_ivec2 {
	int	x;
	int	y;
}				t_ivec2;


typedef struct	s_img {
	uint16_t	w;
	uint16_t	h;
	uint8_t		*data;
}				t_img;


typedef struct s_d {
	GLFWwindow	*window;
	int			width;
	int			height;


	GLuint		vertex_sh;
	GLuint		fragment_sh;
	GLuint		program;

	size_t		nbr_of_objects;

	float		*vertices[MAX_OBJECTS_NBR];
	float		*colors[MAX_OBJECTS_NBR];

	size_t		sizeof_vertices[MAX_OBJECTS_NBR];
	size_t		sizeof_colors[MAX_OBJECTS_NBR];

	GLuint		buffer[MAX_OBJECTS_NBR];
	GLuint		vao[MAX_OBJECTS_NBR];

	t_mat4x4	projection;

	t_mat4x4	modelview[MAX_OBJECTS_NBR];

	float		float_projection[4 * 4];
	float		float_modelview[MAX_OBJECTS_NBR][4 * 4];

	t_img		img[255];
	uint16_t	max_img_id;
}					t_d;

struct s_face {
	int		v_index[MAX_VERTICES_FACE];
	int		t_index[MAX_VERTICES_FACE];
	int		vn_index[MAX_VERTICES_FACE];

	uint8_t	v_nbr;
};

typedef struct	s_obj {
	char			*name;

	char			*material;

	t_vec3			vertices[MAX_VERTICES_NBR];
	int				vertices_nbr;

	t_vec3			tex_vertices[MAX_VERTICES_NBR];
	int				tex_vertices_nbr;

	t_vec3			normales[MAX_VERTICES_NBR];
	int				normales_nbr;

	struct s_face	faces[MAX_VERTICES_NBR];
	int				faces_nbr;

	int8_t	error;
}				t_obj;


typedef void (t_obj_func)(char *, t_obj *);

struct	s_obj_parsing {
	char		*name;
	t_obj_func	*f;
};

uint32_t	get_conv_32(const uint32_t *nbr);
uint64_t	get_conv_64(const uint64_t *nbr);
uint8_t		reverse_byte_ptr(const uint8_t *input);
uint8_t		reverse_byte(const uint8_t in);


uint8_t			create_image_from_png(t_d *data, int id_img, const char *name);

GLuint	create_and_compile_shader(const char *filename, GLenum shaderType);
GLuint	create_and_link_program(GLuint vertex_sh, GLuint fragment_sh);

void	debut_handle(char **line, t_obj *ret, int size);
t_obj	obj_parser_main(char *file);

void	handle_mtllib(char *line, t_obj *ret);
void	handle_usemtl(char *line, t_obj *ret);
void	handle_s(char *line, t_obj *ret);
void	handle_o(char *line, t_obj *ret);
void	handle_v(char *line, t_obj *ret);
void	handle_vn(char *line, t_obj *ret);

void	handle_f(char *line, t_obj *ret);

char	**split_whitespace(char const *s);

int		check_float(char *str);
float	ft_atof(char *str);
int8_t	free_str_dtab(char **tab);



#endif
