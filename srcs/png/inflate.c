#include <scop.h>
#include <png.h>

void	create_fixed_huffman(struct s_huff_decode *b,
	struct s_huff_decode *c)
{
	int16_t i;

	i = -1;
	while (++i <= 143)
		b->len[i] = (struct s_length_code){8, 0, i};
	i--;
	while (++i <= 255)
		b->len[i] = (struct s_length_code){9, 0, i};
	i--;
	while (++i <= 279)
		b->len[i] = (struct s_length_code){7, 0, i};
	i--;
	while (++i <= 287)
		b->len[i] = (struct s_length_code){8, 0, i};
	get_code_from_lengths(b->len, 288);
	i = -1;
	while (++i < 32)
		c->len[i] = (struct s_length_code){5, 0, i};
	get_code_from_lengths(c->len, 32);
	b->tree = create_tree(b->len, 288);
	c->tree = create_tree(c->len, 32);
}

void	create_dynamic_huffman(struct s_huff_decode *b,
	struct s_huff_decode *c, uint8_t *data, struct s_bit_and_byte *current)
{
	struct s_huff_decode	a;
	struct s_length_code	a_lens[19];
	size_t					i;

	ft_bzero(a_lens, sizeof(a_lens));
	a.len = a_lens;
	b->size = read_n_bits(data, current, 5) + 257;
	c->size = read_n_bits(data, current, 5) + 1;
	a.size = read_n_bits(data, current, 4) + 4;
	i = -1;
	while (++i < 19)
	{
		a.len[g_a_init[i].symbol].symbol = g_a_init[i].symbol;
		if (i < a.size)
			a.len[g_a_init[i].symbol].length = read_n_bits(data, current, 3);
	}
	get_code_from_lengths(a.len, 19);
	a.tree = create_tree(a.len, 19);
	get_len_list(data, current, b, a.tree);
	get_code_from_lengths(b->len, b->size);
	b->tree = create_tree(b->len, b->size);
	get_len_list(data, current, c, a.tree);
	get_code_from_lengths(c->len, c->size);
	c->tree = create_tree(c->len, c->size);
	delete_tree(a.tree);
}

void	write_from_len_and_dist(uint16_t sym,
	struct s_bit_and_byte *current, struct s_png_img *img,
	struct s_huff_decode c)
{
	uint16_t					len;
	uint16_t					distance;
	size_t						i;

	len = g_length_codes_base_len[sym - 257][1] +
	(int)read_n_bits(current->data,
		current, g_length_codes_base_len[sym - 257][0]);
	distance = get_next_symbol(current->data, current, c.tree);
	distance = g_dist_base_len[distance][1] + (int)read_n_bits(current->data,
		current, g_dist_base_len[distance][0]);
	i = 0;
	while (i < len)
	{
		if (*img->index + i >= distance)
			img->data[i + *img->index] = img->data[*img->index - distance + i];
		else
			exit(printf("Error 184\n"));
		i++;
	}
	*(img->index) += len;
}

uint8_t	process_block(uint8_t *image, size_t *index_in_img,
	struct s_bit_and_byte *current)
{
	uint16_t					sym;
	struct s_huff_decode		b;
	struct s_huff_decode		c;
	uint8_t						final;

	init_png_value(current, &b, &c, &final);
	sym = 0;
	while (sym != 256)
	{
		sym = get_next_symbol(current->data, current, b.tree);
		if (sym < 256)
		{
			image[*index_in_img] = sym;
			(*index_in_img)++;
		}
		else if (sym > 256)
			write_from_len_and_dist(sym, current,
				&(struct s_png_img){index_in_img, image}, c);
	}
	delete_tree(b.tree);
	delete_tree(c.tree);
	free(b.len);
	free(c.len);
	return (final);
}

void	*png_inflate(uint8_t *data, uint8_t *dst)
{
	size_t						index_in_img;
	struct s_bit_and_byte		current;

	index_in_img = 0;
	current.data = data + 2;
	current.bit = 0;
	current.byte = 0;
	while (!process_block(dst, &index_in_img, &current))
		;
	return (NULL);
}
