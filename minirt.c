/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minirt.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: migo <migo@student.42seoul.kr>			 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/04/24 11:53:10 by migo			  #+#	#+#			 */
/*   Updated: 2023/05/15 15:11:43 by migo			 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minirt.h"

void	reset(t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			my_mlx_pixel_put(img, i, j, 0x00000000);
			j++;
		}
		i++;
	}
}

void	render(t_data *data, t_set *set, double width, double height)
{
	int		j;
	int		i;
	float	u;
	float	v;
	t_ray	r;

	j = -1;
	while (++j < height)
	{
		i = -1;
		while (++i < width)
		{
			u = (double)i / (width - 1);
			v = (height - (double)j - 1) / (height - 1);
			r.orig = set->cam.loc;
			r.dir = v_add(set->cam.lower_left_corner, \
					v_sub(v_add(v_mul_n(set->cam.hor, u), \
					v_mul_n(set->cam.ver, v)), set->cam.loc));
			r.dir = unit_vector(r.dir);
			my_mlx_pixel_put(data, i, j, ray_color(r, set));
		}
	}
}

int	main_loop( t_data *img)
{
	reset(img);
	img->set.cam.lower_left_corner = set_lower_left_corner(&img->set.cam);
	render(img, &(img->set), WIDTH, HEIGHT);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	img;

	if (argc != 2)
		return (printf("parameter error"));
	checkmap(argv, &(img.set));
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "ray tracing");
	img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	rt_hook(&img);
	mlx_loop_hook(img.mlx, main_loop, &img);
	mlx_loop(img.mlx);
}
