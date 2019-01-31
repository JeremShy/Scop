#include <scop.h>
#include <png.h>

static void	write_length_code(struct s_length_code *len,
	uint16_t occurency, size_t *index_in_len, uint16_t sym)
{
	size_t		i;

	i = 0;
	while (i < occurency)
	{
		if (sym == 16)
			len[*index_in_len] = (struct s_length_code){
				len[*index_in_len - 1].length, 0, *index_in_len};
		else
			len[*index_in_len] = (struct s_length_code){0, 0, *index_in_len};
		(*index_in_len)++;
		i++;
	}
}

uint64_t	read_n_bits(uint8_t *data, struct s_bit_and_byte *current,
	size_t len)
{
	uint64_t	ret;
	size_t		n;
	uint8_t		start_bit;

	ret = 0;
	n = len;
	start_bit = current->bit;
	while (n)
	{
		ret |= ((data[current->byte] >> current->bit) & ((1 << n) - 1))
		<< (len - n);
		n = (n < 8 - current->bit ? 0 : (n - (8 - current->bit)));
		current->bit = (start_bit + len - n) % 8;
		if (current->bit == 0)
			(current->byte)++;
	}
	return (ret);
}

uint16_t	get_next_symbol(uint8_t *data, struct s_bit_and_byte *current,
	struct s_tree *tree)
{
	uint8_t	bit;

	while (tree->l || tree->r)
	{
		bit = read_n_bits(data, current, 1);
		if (!bit)
			tree = tree->l;
		else
			tree = tree->r;
	}
	return (tree->symbol);
}

uint8_t		init_png_value(struct s_bit_and_byte	*current,
	struct s_huff_decode *b, struct s_huff_decode *c, uint8_t *final)
{
	enum e_compression_method	compression_method;

	b->len = malloc(sizeof(struct s_length_code) * 288);
	c->len = malloc(sizeof(struct s_length_code) * 32);
	ft_bzero(b->len, sizeof(struct s_length_code) * 288);
	ft_bzero(c->len, sizeof(struct s_length_code) * 32);
	*final = read_n_bits(current->data, current, 1);
	compression_method = read_n_bits(current->data, current, 2);
	if (compression_method == no_compression || compression_method == invalid)
	{
		ft_putendl_fd("not handled or invalid.", 2);
		return (0);
	}
	if (compression_method == dynamic_huffman)
		create_dynamic_huffman(b, c, current->data, current);
	else if (compression_method == fixed_huffman)
		create_fixed_huffman(b, c);
	return (1);
}

void		get_len_list(uint8_t *data,
	struct s_bit_and_byte *current,
	struct s_huff_decode *dst, struct s_tree *a)
{
	size_t		i;
	uint16_t	sym;

	i = 0;
	while (i < dst->size)
	{
		sym = get_next_symbol(data, current, a);
		if (sym <= 15)
		{
			dst->len[i] = (struct s_length_code){sym, 0, i};
			i++;
		}
		else if (sym == 16)
			write_length_code(dst->len, 3 + read_n_bits(data,
				current, 2), &i, sym);
		else if (sym == 17)
			write_length_code(dst->len, 3 + read_n_bits(data,
				current, 3), &i, sym);
		else if (sym == 18)
			write_length_code(dst->len, 11 + read_n_bits(data,
				current, 7), &i, sym);
		else
			exit(printf("Error 132\n"));
	}
}
