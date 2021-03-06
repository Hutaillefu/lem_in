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

int		parse_num_ants(t_world *world)
{
	char	*line;

	if (!world)
		return (0);
	line = NULL;
	if (get_next_line(0, &line) && ft_strisdigit(line) && ft_atoi(line) >= 0)
	{
		world->nb_ants = ft_atoi(line);
		add_print(&(world->print), line, 1);
		ft_strdel(&line);
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

t_room	*parse_room(t_world *world, const char *line)
{
	char	**values;
	t_room	*room;

	values = NULL;
	room = NULL;
	if (*line == 'L' || *line == '#' || !(values = ft_strsplit(line, ' ')))
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
	add_print(&(world->print), (char *)line, 1);
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
	if (!world || !pre_line)
		return (0);
	if (!get_next_line(0, &line))
		return (0);
	add_print(&(world->print), (char *)pre_line, 1);
	if ((ft_strcmp("start", &(pre_line[2])) == 0 && world->start_room) ||
		(ft_strcmp("end", &(pre_line[2])) == 0 && world->end_room))
	{
		ft_strdel(&line);
		return (0);
	}
	if ((ft_strcmp("start", &(pre_line[2])) == 0 &&
		setup_room(&world, line, 0)) ||
		(ft_strcmp("end", &(pre_line[2])) == 0 &&
		setup_room(&world, line, 1)))
	{
		ft_strdel(&line);
		return (1);
	}
	return (0);
}

int		parse_link(const char *line, t_world *world)
{
	char	**values;
	int		start_index;
	int		end_index;

	if (!line || !world || !(world->start_room) || !(world->end_room)
	|| (!(world->links) && !init_links(world)) ||
	!(values = ft_strsplit(line, '-')))
		return (0);
	if (ft_tablen(values) != 2 ||
		(start_index = get_room_index(world, values[0])) < 0 ||
		(end_index = get_room_index(world, values[1])) < 0 ||
		!add_link(world, start_index, end_index))
	{
		ft_free_tab(values);
		return (0);
	}
	add_print(&(world->print), (char *)line, 1);
	ft_free_tab(values);
	return (1);
}

/*
  ** Parse stdin input into world object.
*/

void	parse_map(t_world *world)
{
	if (!world)
		return ;
	if (!parse_rooms(world))
	{
		if (world->print[ft_strlen(world->print)] != '\n')
			add_print(&(world->print), "\n", 0);
		return ;
	}
	if (!parse_links(world))
	{
		if (world->print[ft_strlen(world->print)] != '\n')
			add_print(&(world->print), "\n", 0);
		return ;
	}
	if (world->print[ft_strlen(world->print)] != '\n')
		add_print(&(world->print), "\n", 0);
}
