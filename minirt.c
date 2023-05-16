/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:53:10 by migo              #+#    #+#             */
/*   Updated: 2023/05/15 15:11:43 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render(t_data *data, t_set *set, double height, double width)
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
			r.orig = set->camera.location;
			r.dir = v_add(set->camera.lower_left_corner, \
					v_sub(v_add(v_mul_n(set->camera.hor, u), \
					v_mul_n(set->camera.ver, v)), set->camera.location));
			r.dir = unit_vector(r.dir);
			my_mlx_pixel_put(data, i, j, ray_color(r, set));
		}
	}
}

int	rt_close(void *param)
{
	exit((int)param);
}

int	key_hook_mng(int keycode, t_data *img)
{
	if (keycode == 53)
		rt_close(img);
	return (0);
}

void	rt_hook(t_data *img)
{
	mlx_hook(img->win, 2, 0, key_hook_mng, img);
	mlx_hook(img->win, 17, 0, rt_close, 0);
}

int	main(int argc, char **argv)
{
	t_set	set;
	t_data	img;

	if (argc != 2)
		return (printf("parameter error"));
	checkmap(argv, &set);
	set.camera.lower_left_corner = set_lower_left_corner(&set.camera);
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, 1200, 800, "ray tracing");
	img.img = mlx_new_image(img.mlx, 1200, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	render(&img, &set, 800, 1200);
	ft_lstclear(&set.objects);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	rt_hook(&img);
	mlx_loop(img.mlx);
}
