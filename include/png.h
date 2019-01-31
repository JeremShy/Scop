#ifndef PNG_H
# define PNG_H

# include <stdint.h>
# include <stddef.h>
# include <sys/stat.h>

# define MAX_BITS 15

# define IHDR 0x49484452
# define IDAT 0x49444154
# define IEND 0x49454E44

typedef struct s_ivec2				t_ivec2;
typedef struct s_img				t_img;

struct								s_png_ihdr
{
	uint32_t	width;
	uint32_t	height;
	uint8_t		bdp;
	uint8_t		color_type;
	uint8_t		compression;
	uint8_t		filter;
	uint8_t		interlace;
	uint8_t		bpp;
};

struct								s_chunk_hdr
{
	uint32_t	length;
	uint32_t	type;
};

struct								s_length_code
{
	uint8_t		length;
	uint16_t	code;
	uint16_t	symbol;
};

enum								e_compression_method
{
	no_compression = 0,
	fixed_huffman = 1,
	dynamic_huffman = 2,
	invalid = 3
};

struct								s_tree
{
	struct s_tree	*l;
	struct s_tree	*r;
	uint16_t		symbol;
};

struct								s_huff_decode
{
	struct s_tree			*tree;
	struct s_length_code	*len;
	uint16_t				size;
};

struct								s_bit_and_byte
{
	uint8_t		*data;
	uint8_t		bit;
	uint32_t	byte;
};

struct								s_png_img
{
	size_t	*index;
	uint8_t	*data;
};

void								get_code_from_lengths(
	struct s_length_code *length_codes, size_t s);
void								*png_inflate(uint8_t *data, uint8_t *dst);
struct s_tree						*create_tree(
	struct s_length_code *codes, size_t s);
void								delete_tree(struct s_tree	*tree);

// void								resize_image(struct s_png_ihdr *png_ihdr,
// 	t_img *dest_img, uint8_t *img_data);

void								copy_source_in_img(
	struct s_png_ihdr *png_ihdr, uint8_t *src_img, uint32_t *dest_img);
void								*init_png_parser(
	const char *name, off_t *size);
struct s_chunk_hdr					*get_next_chunk(void *current_chunk);
int64_t								print_and_ret(const char *str,
	void *addr, off_t file_size, uint8_t *compressed_data);
uint8_t								check_and_read_ihdr(void *addr,
	struct s_png_ihdr *png_ihdr);

uint8_t								apply_filter(
	uint8_t filter, uint8_t *data, struct s_png_ihdr *png_ihdr, size_t i);

void								create_fixed_huffman(
	struct s_huff_decode *b, struct s_huff_decode *c);
void								create_dynamic_huffman(
	struct s_huff_decode *b, struct s_huff_decode *c,
	uint8_t *data, struct s_bit_and_byte *current);

uint64_t							read_n_bits(uint8_t *data,
	struct s_bit_and_byte *current, size_t len);
uint16_t							get_next_symbol(uint8_t *data,
	struct s_bit_and_byte *current, struct s_tree *tree);
uint8_t								init_png_value(
	struct s_bit_and_byte *current, struct s_huff_decode *b,
	struct s_huff_decode *c, uint8_t *final);
void								get_len_list(
	uint8_t *data, struct s_bit_and_byte *current,
	struct s_huff_decode *dst, struct s_tree *a);

uint8_t								left(uint8_t *data, size_t i,
	struct s_png_ihdr *png_ihdr);
uint8_t								prior(uint8_t *data, size_t i,
	struct s_png_ihdr *png_ihdr);
uint8_t								prior_left(uint8_t *data, size_t i,
	struct s_png_ihdr *png_ihdr);
uint8_t								paeth_predictor(int a, int b, int c);

extern const struct s_length_code	g_a_init[19];
extern const int					g_length_codes_base_len[][2];
extern const int					g_dist_base_len[][2];

#endif
