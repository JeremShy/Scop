#include <libftmatrices.h>

void	ft_mat4x4_print(const t_mat4x4 matrice)
{
	int	i;

	i = 0;
	printf("-----------------------------------------------------------------\n");
	while (i < 4)
	{
		printf("|\t%-4f|\t%-4f|\t%-4f|\t%-4f|\n", matrice[i][0], matrice[i][1],
			matrice[i][2], matrice[i][3]);
		i++;
	}
	printf("-----------------------------------------------------------------\n");
}
