/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:49:20 by magouin           #+#    #+#             */
/*   Updated: 2019/02/26 15:49:53 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# define STB_IMAGE_IMPLEMENTATION
# define GL_SILENCE_DEPRECATION
# define GLFW_INCLUDE_GLCOREARB

# define MAX_VERTICES_NBR 8192 * 2
# define MAX_OBJECTS_NBR 16
# define MAX_VERTICES_FACE 16

# define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

# define G_OFFSET 0
# define T_OFFSET 1
# define V_OFFSET 2
# define O_OFFSET 3
# define F_OFFSET 4

# include <stdio.h>
# include <sys/time.h>
# include <libft.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <GLFW/glfw3.h>
# include <libftmatrices.h>
# include <sys/mman.h>

typedef struct	s_ivec2 {
	int	x;
	int	y;
}				t_ivec2;

typedef struct	s_img {
	uint16_t	w;
	uint16_t	h;
	uint8_t		*data;
}				t_img;

struct			s_cam
{
	t_mat4x4	view;
	t_mat4x4	proj;
	GLfloat		view_f[16];
	GLfloat		proj_f[16];
	t_vec3		up;
};

struct			s_gl_buff
{
	GLuint	ebo;
	GLuint	vao;
	GLuint	vbo;
};

struct			s_face
{
	int		v_index[MAX_VERTICES_FACE];
	int		vt_index[MAX_VERTICES_FACE];
	int		vn_index[MAX_VERTICES_FACE];

	uint8_t	v_nbr;
};

struct			s_mtl
{
	char	*ref;
	char	*img_file;
	int		index;
};

struct			s_ref
{
	char	*ref;
	char	*img;
};

struct			s_point
{
	t_vec3	vertex;
	t_vec2	tex_vertex;
	float	rand;
	t_vec3	normal;
};

typedef struct	s_obj
{
	char				*name;
	char				*path;

	t_vec3				*vertices;
	uint				vertices_nbr;
	int					vertices_curr;

	uint				textures_nbr;

	t_vec2				*tex_vertices;
	uint				tex_vertices_nbr;
	int					tex_vertices_curr;

	t_vec3				*normales;
	uint				normales_nbr;
	int					normales_curr;

	struct s_face		*faces;
	uint				faces_nbr;
	int					faces_curr;

	uint				indices_nbr;
	uint				*indices;

	struct s_point		*points;

	GLvoid				**offset;
	GLsizei				*counts;

	struct s_ref		*ref;
	uint				ref_nbr;

	struct s_mtl		*mtls;
	uint				mtl_nbr;
	uint				mtl_curr;

	uint8_t				init;
	t_vec3				min;
	t_vec3				max;

	int8_t				error;
	struct s_gl_buff	gl_buff;
	t_vec3				mid;
	t_vec3				pos;
	float				scale;
	int					roton;
	int					texon;
	float				texfade;
	int					texonloc;
	int					modelloc;
	int					deftex;
	t_mat4x4			model;
	GLfloat				model_f[16];

}				t_obj;

typedef struct	s_d
{
	GLFWwindow			*window;
	int					width;
	int					height;
	struct s_cam		cam;
	GLuint				vertex_sh;
	GLuint				fragment_sh;
	GLuint				program;

	size_t				object_nbr;
	size_t				texture_nbr;

	GLuint				buffer[MAX_OBJECTS_NBR];
	GLuint				vao[MAX_OBJECTS_NBR];

	t_mat4x4			projection;

	t_mat4x4			modelview[MAX_OBJECTS_NBR];

	float				float_projection[4 * 4];
	float				float_modelview[MAX_OBJECTS_NBR][4 * 4];

	t_img				*imgs;
	uint16_t			max_img_id;
	t_vec3				eye;
	t_vec3				dir;

	uint8_t				drawing_mode;
	float				angle_y;
	int					viewloc;
	int					projloc;
	int					ambloc;
	int					lightloc;
	int					lightcolorloc;
	int					eyeloc;

	t_obj				*current;
	float				depl;
	float				ambient;
	t_vec3				lightpos;
	t_vec3				lightcolor;
}				t_d;

typedef void	(t_obj_func)(char *, t_obj *);
typedef void	(t_key_func)(t_d *, t_obj *, uint, char *);

struct			s_obj_parsing {
	char		*name;
	t_obj_func	*f;
};

struct			s_key_event
{
	uint		key;
	t_key_func	*func;
};

uint32_t		get_conv_32(const uint32_t *nbr);
uint64_t		get_conv_64(const uint64_t *nbr);
uint8_t			reverse_byte_ptr(const uint8_t *input);
uint8_t			reverse_byte(const uint8_t in);
void			fclamp(float *f, float min, float max);

uint8_t			create_image_from_png(t_d *data, int id_img, const char *name);

GLuint			create_and_compile_shader(const char *filename,
	GLenum shadertype);
GLuint			create_and_link_program(GLuint vertex_sh, GLuint fragment_sh);

void			debut_handle(char **line, t_obj *ret, int size);
t_obj			obj_parser_main(char *file);

void			handle_mtllib(char *line, t_obj *ret);
void			handle_usemtl(char *line, t_obj *ret);
void			handle_s(char *line, t_obj *ret);
void			handle_g(char *line, t_obj *ret);
void			handle_o(char *line, t_obj *ret);
void			handle_v(char *line, t_obj *ret);
void			handle_vn(char *line, t_obj *ret);
void			handle_vt(char *line, t_obj *ret);
void			handle_f(char *line, t_obj *ret);

void			init_obj(t_obj *obj);
int				init_path(char *param, t_obj *obj);
void			init_malloc(t_obj *ret, char *file);

size_t			find_next_line(char *line);
int8_t			is_whitespace(char c);
int				ignore_whitespaces(char **line);
int				find_next_ignored_char(char *line);
int8_t			ignored_line(char *line);
char			**split_whitespace(char const *s);

void			fill_ref(t_obj *obj, char *file, size_t size);
void			create_ref(t_obj *obj, char *file, size_t size);
void			fill_mtl(t_obj *obj);
void			fill_point_from_face(t_obj *obj, uint i, int *curr);

void			debut_handle(char **line, t_obj *ret, int size);
void			next_line(char **file, size_t *size);
void			parse_line(char *line, t_obj *ret);

void			*open_file(char *file, size_t *size);
int				get_values_for_malloc(t_obj *ret, char *file);

int				check_float(char *str);
float			ft_atof(char *str);
int8_t			free_str_dtab(char **tab);

void			echap(t_d *data, t_obj *objs, uint delta, char *prev);
void			key_0(t_d *data, t_obj *objs, uint delta, char *prev);
void			key_1(t_d *data, t_obj *objs, uint delta, char *prev);
void			key_2(t_d *data, t_obj *objs, uint delta, char *prev);
void			key_3(t_d *data, t_obj *objs, uint delta, char *prev);
void			key_4(t_d *data, t_obj *objs, uint delta, char *prev);
void			key_5(t_d *data, t_obj *objs, uint delta, char *prev);
void			key_6(t_d *data, t_obj *objs, uint delta, char *prev);
void			key_7(t_d *data, t_obj *objs, uint delta, char *prev);
void			key_8(t_d *data, t_obj *objs, uint delta, char *prev);
void			key_9(t_d *data, t_obj *objs, uint delta, char *prev);
void			equal(t_d *data, t_obj *objs, uint delta, char *prev);
void			minus(t_d *data, t_obj *objs, uint delta, char *prev);
void			w(t_d *data, t_obj *objs, uint delta, char *prev);
void			s(t_d *data, t_obj *objs, uint delta, char *prev);
void			a(t_d *data, t_obj *objs, uint delta, char *prev);
void			d(t_d *data, t_obj *objs, uint delta, char *prev);
void			t(t_d *data, t_obj *objs, uint delta, char *prev);
void			r(t_d *data, t_obj *objs, uint delta, char *prev);
void			v(t_d *data, t_obj *objs, uint delta, char *prev);
void			o(t_d *data, t_obj *objs, uint delta, char *prev);
void			key_up(t_d *data, t_obj *objs, uint delta, char *prev);
void			key_down(t_d *data, t_obj *objs, uint delta, char *prev);
void			key_right(t_d *data, t_obj *objs, uint delta, char *prev);
void			key_left(t_d *data, t_obj *objs, uint delta, char *prev);

void			init_vbo(t_obj *obj);
void			init_vao(t_obj *obj);
void			init_uniform_data(t_d *data);
void			init_uniform_obj(t_d *data, t_obj *obj);
void			init_frame(t_d *data, uint delta, t_obj *objs);

t_obj			*get_all_obj(t_d *data, int ac, char **av);
void			get_glteximage(uint *texs, uint *i_tex, t_d *data, char *file);
uint			*init_texs(t_d *data, t_obj *objs);
void			draw_part_obj(t_obj *obj, uint *x, uint *texs);
void			draw_obj(t_obj *obj, float angle, uint *x, uint *texs);

int8_t			init_data(t_d *data);
void			error_callback(int error, const char *description);
int8_t			init_shaders(t_d *data, const char *frag, const char *vert);
int8_t			init_glfw(t_d *data);
int8_t			init_all(t_d *data);

void			key_event(t_d *data, uint delta, t_obj *objs);
void			rotation_cam(t_d *data, uint delta);

#endif
