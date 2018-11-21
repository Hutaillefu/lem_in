/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pathfinding_tools.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/21 15:22:40 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 15:22:41 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
  ** Return true if a link exist between 'from' and 'to'
  ** and the target room 'to' has no ant (except for end_room).
*/

int		is_joinable(t_world *world, t_room *from, t_room *to)
{
	int from_index;
	int to_index;

	if (!world || !(world->links) || !from || !to)
		return (0);
	if ((from_index = get_room_index(world, from->name)) < 0 ||
	(to_index = get_room_index(world, to->name)) < 0)
		return (0);
	if (is_link_exist(world->links[from_index][to_index]) &&
	ft_strcmp(to->name, world->end_room->name) == 0)
		return (1);
	return ((is_link_exist(world->links[from_index][to_index]) ||
	is_link_exist(world->links[to_index][from_index])) && to->num_ant == 0);
}

/*
  ** Return true if a link is free between 'from' and 'to' or
  ** between 'to' and 'from'
*/

int		can_join(t_world *world, t_room *from, t_room *to)
{
	int from_index;
	int to_index;

	if (!world || !(world->links) || !from || !to)
		return (0);
	if ((from_index = get_room_index(world, from->name)) < 0 ||
	(to_index = get_room_index(world, to->name)) < 0)
		return (0);
	return (is_link_free(world->links[from_index][to_index]) ||
	is_link_free(world->links[to_index][from_index]));
}
