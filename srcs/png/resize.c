#include <scop.h>
#include <png.h>

void		clamp(int32_t *point, int32_t min, int32_t max)
{
	*point < min ? (*point = min) : 0;
	*point > max ? (*point = max) : 0;
}
