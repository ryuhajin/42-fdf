# include "fdf.h"

typedef struct s_img
{
	void * mlx_img; //mlx_img 는 mlx_new_image 함수가 반환하는 주소를 참조한다.
	char * addr;
	int bits_per_pixel; //픽셀 당 몇 비트가 할당되는가 //보통 ARGB는 알파벳 하나당 8비트. 즉 32비트 = 4바이트.
	int line_length; // 한 줄당 몇 바이트인가
	int endian;
} t_img; // mlx image를 사용하는데 필요한 모든 내용이 담긴 구조체
// mlx_new_image 함수는 공유 메모리 상에 가로, 세로 해상도 만큼의 공간을 할당하는듯. 도화지 생성?
// 이미지의 픽셀을 직접 변경하기 위해서는 메모리 상에 있는 이미지의 주소가 필요하다.

typedef struct s_data
{
	void * mlx_ptr;
	void * win_ptr;
	t_img img;
} t_data;

typedef struct rect
{ //x,y는 시작 좌표
	int x;
	int y;
	int height;
	int width;
	int color;
} t_rect;

void img_pix_put (t_img * img, int x, int y, int color)
{
	char * pixel;
	//line_length = width * 4 (가로 길이 * int 4byte)
	//bit_per_pixel = pixel bit == 32 (int 4byte)
	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	//0,0에서 시작한 포인터를 x,y만큼 움직이기
	*(int *)pixel = color; // 좌표만큼 도화지를 움직인 후 해당 좌표에 점 찍기 (컬러를 넣어서)
}

void render_background (t_img * img, int color)
{
	int i;
	int j;

	i = 0;
	while (i < 1000)
	{
		j = 0;
		while (j < 1000)
		{
			img_pix_put(img, j++, i, color);
		}
		i++;
	}
}

int render_rect (t_img * img, t_rect rect)
{
	int i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
		{
			img_pix_put(img, j++, i, rect.color);
		}
		i++;
	}
	return 0;
}

int	render(t_data *data)
{
    if (data->win_ptr == NULL)
        return (1);
    render_background(&data->img, 16777215); // 백그라운드 먼저 찍고
    render_rect(&data->img, (t_rect){0, 0,
        100, 100, 16777081});
    render_rect(&data->img, (t_rect){500, 500, 500, 300, 16726649}); // 그 뒤 사각형 찍기

    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	//mlx_put_image_to_window 함수를 통해 업데이트된 이미지를 window에 푸시함!!!
	// 이 작업은 이미지의 좌표는 창 전체를 덮고 있기 때문에 (0, 0)입니다.
	//mlx_put_image_to_window 함수는 각 프레임에서 이미지와 이미지에 적용된 변경 사항(있는 경우)을 푸시합니다.
    return (0);
}

int main(void)
{
	t_data * data;
	void * mlx;

	data = malloc(sizeof(t_data) * 1);

	mlx = mlx_init();
	data->mlx_ptr = mlx;
	if (data->mlx_ptr == NULL)
		return 0;
	data->win_ptr = mlx_new_window(mlx, 1000, 1000, "test");
	if (data->win_ptr == NULL)
		return 0;
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, 1000, 1000);
	data->img.line_length = 1000 * 4;
	data->img.bits_per_pixel = 32;
	data->img.endian = 0;
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	//mlx_get_data_addr 함수는 이미지의 실제 주소를 단순한 픽셀 배열로 반환한다.
	//char * 포인터를 리턴하는데, 이는 일반적으로 image 공간을 한 번에 한 바이트씩 탐색한다는 것을 의미합니다.
	//특정 x,y 좌표로 픽셀을 찾아야하지만 실질적으로 get_data_addr 함수는 2차원이 아니라 1차원 배열을 다룬다.

	render(data);
	mlx_loop(mlx);
	return 0;
}
