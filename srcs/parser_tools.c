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

int		setup_room(t_world *world, char *line, t_room **room)
{
	t_room	*new_room;

	if (!world || !room || (*room))
		return (0);
	if (!(new_room = parse_room(world, line)))
		return (0);
	*room = new_room;
	(world->nb_rooms)++;
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
