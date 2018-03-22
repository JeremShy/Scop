#include <libftmatrices.h>

void    ft_mat4x4_to_float_array(float dest[16], t_mat4x4 matrice)
{
    int i;
    int j;

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            dest[j * 4 + i] = matrice[i][j];
            j++;
        }
        i++;
    }
}
