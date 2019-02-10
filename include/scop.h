#ifndef SCOP_H
# define SCOP_H

# include <stdio.h>
# include <sys/time.h>
# include <libft.h>
# include <sys/stat.h>
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <libftmatrices.h>

# include <sys/mman.h>

# define MAX_VERTICES_NBR 8192 * 2
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

struct	s_cam
{
	t_mat4x4	view;
	t_mat4x4	proj;
	t_mat4x4	model;
	GLfloat		view_f[16];
	GLfloat		proj_f[16];
	GLfloat		model_f[16];
	t_vec3		up;
};

typedef struct		s_d {
	GLFWwindow		*window;
	int				width;
	int				height;
	struct s_cam	cam;
	GLuint			vertex_sh;
	GLuint			fragment_sh;
	GLuint			program;

	size_t			object_nbr;
	size_t			texture_nbr;

	GLuint			buffer[MAX_OBJECTS_NBR];
	GLuint			vao[MAX_OBJECTS_NBR];

	t_mat4x4		projection;

	t_mat4x4		modelview[MAX_OBJECTS_NBR];

	float			float_projection[4 * 4];
	float			float_modelview[MAX_OBJECTS_NBR][4 * 4];

	t_img			*imgs;
	uint16_t		max_img_id;
	t_vec3			eye;
	t_vec3			dir;

	GLint			texture_on;
	uint8_t			drawing_mode;
	float			angle_y;
	int				last_state[GLFW_KEY_LAST];
	// int				color_on;
}					t_d;

struct s_face {
	int		v_index[MAX_VERTICES_FACE];
	int		t_index[MAX_VERTICES_FACE];
	int		vn_index[MAX_VERTICES_FACE];

	uint8_t	v_nbr;
};

struct s_mtl
{
	char	*ref;
	char	*img_file;
	int		index;
};

struct				s_ref
{
	char			*ref;
	char			*img;
}					;

typedef struct		s_obj {
	char			*name;
	char			*path;

	t_vec3			*vertices;
	uint			vertices_nbr;
	int				vertices_curr;

	t_vec2			*textures; // Normale ??

	t_vec2			*tex_vertices;
	uint			tex_vertices_nbr;
	int				tex_vertices_curr;

	t_vec3			*normales;
	uint			normales_nbr;
	int				normales_curr;

	struct s_face	*faces;
	uint			faces_nbr;
	int				faces_curr;
	
	uint			indices_nbr;
	uint			*indices;
	GLvoid			**offset;
	
	GLsizei			*counts;

	struct s_ref	*ref;
	uint			ref_nbr;

	struct s_mtl	*mtls;
	uint			mtl_nbr;
	uint			mtl_curr;

	uint8_t			init;
	t_vec3			min;
	t_vec3			max;

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
void	handle_g(char *line, t_obj *ret);
void	handle_o(char *line, t_obj *ret);
void	handle_v(char *line, t_obj *ret);
void	handle_vn(char *line, t_obj *ret);
void	handle_vt(char *line, t_obj *ret);

void	handle_f(char *line, t_obj *ret);

char	**split_whitespace(char const *s);
int		ignore_whitespaces(char **line);
int8_t	is_whitespace(char c);

int		check_float(char *str);
float	ft_atof(char *str);
int8_t	free_str_dtab(char **tab);



#endif
