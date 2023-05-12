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

double	skip_space_comma(char **map)
{
	int		flag;
	double	m_flag;

	m_flag = 1;
	flag = 0;
	while (*map[0] == ' ' || (*map[0] >= 9 && *map[0] < 13) || *map[0] == ',')
	{
		if (*map[0] == ',')
			flag++;
		(*map)++;
	}
	if (flag > 1)
		exit(printf(", error"));
	if (*map[0] == '-')
	{
		m_flag = -1;	
		(*map)++;
	}
	return (m_flag);
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
	close(fd);
}