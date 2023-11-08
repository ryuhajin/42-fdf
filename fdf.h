/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:17:11 by dayou             #+#    #+#             */
/*   Updated: 2023/11/08 21:47:27 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h> //perror
# include <unistd.h>
# include <fcntl.h>
# include "./mlx/mlx.h" // make 같이 하는데 필요할까?
# include <math.h>

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

void render_background (t_img * img, int color);
int	render(t_data *data, int x1, int x2, int y1, int y2, int color);
void img_pix_put (t_img * img, int x, int y, int color);
void line_draw (int x1, int y1, int x2, int y2, t_img * img, int color);

#endif
