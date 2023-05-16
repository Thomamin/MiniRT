/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:25:15 by migo              #+#    #+#             */
/*   Updated: 2023/05/16 14:25:50 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	classification_map(char *map, int i, t_set *set)
{
	if (map[i] == 'C')
		set_camera(&set->camera, &map[i]);
	else if (map[i] == 'A')
		set_am_light(&set->am_light, &map[i]);
	else if (map[i] == 'L')
		set_light(&set->light, &map[i]);
	else if (map[i] == 's' && map[i + 1] == 'p')
		ft_lstadd_front(&set->objects, ft_lstnew(0, &map[i]));
	else if (map[i] == 'p' && map[i + 1] == 'l')
		ft_lstadd_front(&set->objects, ft_lstnew(2, &map[i]));
	else if (map[i] == 'c' && map[i + 1] == 'y')
		ft_lstadd_front(&set->objects, ft_lstnew(1, &map[i]));
	else
	{
		if (map[i] != '\0')
			exit(printf("%c is wrong parameter", map[i]));
	}
}

double	check_dot(char **map, double flag)
{
	if ((*map)[-1] >= '0' && (*map)[-1] <= '9')
	{
		if ((*map)[-1] >= '0' && (*map)[-1] <= '9')
		{
			if (flag == 0)
				return (1);
		}
	}
	exit(printf("dot error\n"));
}

double	ft_atof(char **map)
{
	double	num;
	double	flag[2];
	double	power;

	num = 0;
	flag[0] = 0;
	flag[1] = skip_space_comma(map);
	power = 1;
	while (1)
	{
		if (*map[0] <= '9' && *map[0] >= '0')
		{
			num = num * 10 + (*map[0] - 48);
			if (flag[0] == 1)
				power *= 10;
		}
		else if (*map[0] == '.')
			flag[0] = check_dot(map, flag[0]);
		else
			break ;
		(*map)++;
	}
	if (*map[0] != ' ' && *map[0] != '\0' && *map[0] != '\n' && *map[0] != ',')
		exit(printf("%c is wrong parameter", *map[0]));
	return (num * flag[1] / power);
}

void	checkmap(char **argv, t_set	*set)
{
	char	*map;
	int		fd;
	int		i;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(printf("open error\n"));
	if (!is_file_name_ok(argv[1]))
		exit(printf("file name error input file extention '.rt' required.\n"));
	while (1)
	{
		i = 0;
		map = get_next_line(fd);
		if (map == NULL)
			break ;
		while (map[i] == ' ' || (map[i] >= 9 && map[i] <= 13))
			i++;
		classification_map(map, i, set);
		free (map);
	}
	if (set->camera.fov == 0)
		exit(printf("Camera must exist \n"));
	close(fd);
}
