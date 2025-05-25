#include "libft.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

//this is a test for the successful linking of the minilibx library
// minilibx window creation 

int	main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (!mlx)
		return (1);

	win = mlx_new_window(mlx, 800, 600, "miniRT");
	if (!win)
		return (1);

    //test of libft functions
    printf("%s\n", ft_itoa(65));
	mlx_loop(mlx);
	return (0);
}
