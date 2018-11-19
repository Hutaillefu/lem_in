/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 19:23:40 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/18 19:23:42 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
  ** Read one line as int and set the number of ants
*/

int	parse_num_ants(t_world *world)
{
	 char	*line;

	if (!world)
		return (0);
	line = NULL;
	if (get_next_line(0, &line) && ft_strisdigit(line))
	{
		world->nb_ants = ft_atoi(line);
		free(line);
		line = NULL;
		return (1);
	}
	return (0);
}

/*
  ** Parse the string data {name, x, y} into room object.
  ** x & y must be int.
*/

t_room	*parse_room(const char *line)
{
	char	**values;
	t_room	*room;

	values = NULL;
	room = NULL;
	if (!(values = ft_strsplit(line, ' ')))
		return (NULL);
	if (ft_tablen(values) != 3 || !ft_strisdigit(values[1]) ||
	!ft_strisdigit(values[2]))
	{
		ft_free_tab(values);
		return (NULL);
	}
	if (!(room = create_room(values[0], ft_atoi(values[1]),
	ft_atoi(values[2]))))
	{
		ft_free_tab(values);
		return (NULL);
	}
	ft_free_tab(values);
	return (room);
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

int		parse_link(const char *line, t_world *world)
{
	char	**values;
	int		start_index;
	int		end_index;

	if (!line || !world)
		return (0);
	if (!(world->links) && !init_links(world))
		return (0);
	if (!(values = ft_strsplit(line, '-')))
		return (0);
	if (ft_tablen(values) != 2)
	{
		ft_free_tab(values);
		return (0);
	}
	start_index = get_room_index(world, values[0]);
	end_index = get_room_index(world, values[1]);
	if (start_index < 0 || end_index < 0 ||
		!is_room_name_exist(world, values[0]) ||
		!is_room_name_exist(world, values[1]) ||
		!add_link(world, start_index, end_index))
	{
		ft_free_tab(values);
		return (0);
	}
	ft_free_tab(values);
	return (1);
}

/*
  ** Parse stdin input into world object.
*/

void	parse_map(t_world *world)
{
	char	*line;
	int		res;

	if (!world)
		return ;
	line = NULL;
	while (get_next_line(0, &line))
	{
		res = 0;
		if (is_active_commentary(line) && !parse_active_commentary(world, line))
			res = 1;
		//else if (is_commentary(line) && !parse_commentary(line))
		else if (is_room(line) && !process_room(line, world))
			res = 1;
		else if (is_link(line) && !parse_link(line, world))
			res = 1;
		free(line);
		line = NULL;
		if (res)
			return ;
	}
}
