/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser_tools.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/21 15:47:47 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 15:47:48 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		setup_room(t_world **world, char *line, int index)
{
	t_room	*new_room;

	if (!world)
		return (0);
	if (!(new_room = parse_room(*world, line)))
		return (0);
	new_room->index = index;
	if (index == 0)
		(*world)->start_room = new_room;
	else if (index == 1)
		(*world)->end_room = new_room;
	((*world)->nb_rooms)++;
	return (1);
}

/*
  ** Parse a room from line and add it to the world's room list.
*/

int		process_room(const char *line, t_world *world)
{
	t_room	*room;

	if (!line || !world)
		return (0);
	if (!(room = parse_room(world, line)))
		return (0);
	if (!(add_room(world, room)))
	{
		free_room(&room);
		return (0);
	}
	return (1);
}

int		parse_commentary(t_world *world, const char *line)
{
	if (!world || !line)
		return (0);
	add_print(&(world->print), (char *)line, 1);
	return (1);
}

int		parse_links(t_world *world)
{
	char	*line;

	if (!world || !(world->start_room) || !(world->end_room))
		return (0);
	line = NULL;
	while (get_next_line(0, &line))
	{
		if (!(is_link(line) && parse_link(line, world)) &&
			(!is_active_commentary(line) && !(is_commentary(line) &&
			parse_commentary(world, line))))
		{
			ft_strdel(&line);
			return (0);
		}
		ft_strdel(&line);
	}
	return (1);
}

int		parse_rooms(t_world *world)
{
	char	*line;

	if (!world)
		return (0);
	line = NULL;
	while (get_next_line(0, &line))
	{
		if (!(is_room(line) && process_room(line, world)) &&
			!(is_active_commentary(line) &&
			parse_active_commentary(world, line) >= 0) &&
			!(is_commentary(line) && parse_commentary(world, line)))
		{
			if (is_link(line) && parse_link(line, world))
			{
				ft_strdel(&line);
				return (1);
			}
			ft_strdel(&line);
			add_print(&(world->print), "\n", 0);
			return (0);
		}
		ft_strdel(&line);
	}
	return (1);
}
