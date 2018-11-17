
/*
  ** Read one line as int and set the number of ants
*/

int	parse_num_ants(t_world *world)
{
	char	*line;
	int	num;

	line = NULL;
	if (!world)
		return (0);
	line = NULL;
	if (get_next_line(0, &line) == -1 || !line)
		return (0);
	num = ft_atoi(line);
	world->nb_ants = num;
	free(line);
	line = NULL;
	return (1);
}

/*
  ** Active commentary read the next line and process it.
*/

int		parse_active_commentary(t_world *world, const char *pre_line)
{
	char	*line;
	t_room	*room;

	line = NULL;
	room = NULL;
	if (!world)
		return (0);
	if (get_next_line(0, &line) == -1 || !line)
		return (0);
	if (ft_strcmp("start", &(pre_line[2])) == 0)
	{
		if (world->start_room || !(room = parse_room(line)))
		{
			free(line);
			line = NULL;
			return (0);
		}
		world->start_room = room;
		(world->nb_rooms)++;
	}
	else if (ft_strcmp("end", &(pre_line[2])) == 0)
	{
		if (world->end_room || !(room = parse_room(line)))
		{
			free(line);
			line = NULL;
			return (0);
		}
		world->end_room = room;
		(world->nb_rooms)++;
	}
	free(line);
	line = NULL;
	return (1);
}
