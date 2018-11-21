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
#include <stdio.h>

/*
  ** Read one line as int and set the number of ants
*/

int		parse_num_ants(t_world *world)
{
	char	*line;

	if (!world)
		return (0);
	line = NULL;
	if (get_next_line(0, &line) && ft_strisdigit(line) && ft_atoi(line) >= 0)
	{
		world->nb_ants = ft_atoi(line);
		free(line);
		line = NULL;
		return (1);
	}
	if (line)
		ft_strdel(&line);
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

int		setup_room(t_world *world, char *line, t_room **room)
{
	t_room	*new_room;

	if (!world || !room || (*room))
		return (0);
	if (!(new_room = parse_room(line)))
		return (0);
	*room = new_room;
	(world->nb_rooms)++;
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
		return (-1);
	if (ft_strcmp("start", &(pre_line[2])) != 0 &&
	ft_strcmp("end", &(pre_line[2])) != 0)
		return (1);
	if (!get_next_line(0, &line))
		return (-1);
	if (ft_strcmp("start", &(pre_line[2])) == 0)
		setup_room(world, line, &(world->start_room));
	else if (ft_strcmp("end", &(pre_line[2])) == 0)
		setup_room(world, line, &(world->end_room));
	free(line);
	line = NULL;
	return (1);
}

int		parse_link(const char *line, t_world *world)
{
	char	**values;
	int		start_index;
	int		end_index;

	if (!line || !world || (!(world->links) && !init_links(world)) ||
	!(values = ft_strsplit(line, '-')))
		return (0);
	if (ft_tablen(values) != 2)
	{
		ft_free_tab(values);
		return (0);
	}
	if ((start_index = get_room_index(world, values[0])) < 0 ||
	(end_index = get_room_index(world, values[1])) < 0 ||
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
		if (is_active_commentary(line) &&
		parse_active_commentary(world, line) >= 0)
			res = 1;
		//else if (is_commentary(line) && !parse_commentary(line))
		else if (is_room(line) && process_room(line, world))
			res = 1;
		else if (is_link(line) && parse_link(line, world))
			res = 1;
		free(line);
		line = NULL;
		if (!res)
			return ;
	}
}
