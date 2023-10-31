#include "mlx.h"

typedef struct s_data
{
	void * img;
	char * addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
  char *dst;

  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  // 괄호 == offset
    *(unsigned int *)dst = color;
}

int main(void)
{
	void *mlx;
	void *mlx_win;
	t_data test;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "test!");
	test.img = mlx_new_image(mlx, 1920, 1080);
	test.addr = mlx_get_data_addr(test.img, &test.bits_per_pixel, &test.line_length, &test.endian);
	
	my_mlx_pixel_put(&test, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, test.img, 0, 0);
	mlx_loop(mlx);
	return 0;
}
