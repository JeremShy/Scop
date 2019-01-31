#include <scop.h>

uint32_t	get_conv_32(const uint32_t *nbr)
{
	return (uint32_t)((*nbr >> 24) | ((*nbr & 0xFF0000) >> 8) |
		((*nbr & 0xFF00) << 8) | (*nbr << 24));
}

uint64_t	get_conv_64(const uint64_t *nbr)
{
	return (get_conv_32((void*)nbr + 4)
		| (uint64_t)get_conv_32((uint32_t*)nbr) << 32);
}

uint8_t		reverse_byte_ptr(const uint8_t *input)
{
	uint8_t	ret;
	uint8_t	in;

	in = *input;
	ret = (in >> 7) | ((in & 64) >> 5) | ((in & 32) >> 3) | ((in & 16) >> 1) | ((in & 8) << 1) | ((in & 4) << 3) | ((in & 1) << 5) | (in << 7);
	return (ret);
}

uint8_t		reverse_byte(const uint8_t in)
{
	uint8_t	ret;

	ret = (in >> 7) | ((in & 64) >> 5) | ((in & 32) >> 3) | ((in & 16) >> 1) | ((in & 8) << 1) | ((in & 4) << 3) | ((in & 1) << 5) | (in << 7);
	return (ret);
}
