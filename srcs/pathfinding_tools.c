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
  ** Return true if 'from'->'to' or 'to'->'from' exist.
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
	return (is_link_exist(world->links[from_index][to_index]) ||
	is_link_exist(world->links[to_index][from_index]));
}

/*
  ** Return true if 'from'->'to' or 'to'->'from' is free.
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

#include <stdio.h>

/*
  ** Return the best move of 'moves'.
*/

t_move	*get_best_move(t_world *world, t_list *moves)
{
	t_list *it;
	t_move *best;
	int		is_ant_best;
	int		is_ant_it;

	if (!moves)
		return (NULL);
	best = (t_move *)moves->content;
	printf("move costs %d to %d, ", best->cost,  best->target_index);
	it = moves->next;
	while (it)
	{
		printf("move costs %d to %d, ", ((t_move *)it->content)->cost,  ((t_move *)it->content)->target_index);
		if (((t_move *)it->content)->cost < best->cost)
			best = (t_move *)it->content;
		else if (((t_move *)it->content)->cost == best->cost)
		{
			is_ant_best = get_room_by_index(world, best->target_index)->num_ant != 0;
			is_ant_it = get_room_by_index(world, ((t_move *)it->content)->target_index)->num_ant != 0;
			if (is_ant_best && !is_ant_it)
				best = (t_move *)it->content;
		}
		it = it->next;
	}
	printf("\n");
	return (best);
}

/*
  ** Desactivate all links from and to 'room'.
*/

void	avoid_path(t_world *world, int room_index)
{
	int i;

	if (!world)
		return;
	i = 0;
	if (room_index == 1)
		return;
	while (i < world->nb_rooms)
	{
		set_link_exist(&(world->links[i][room_index]), 0);
		set_link_exist(&(world->links[room_index][i]), 0);
		i++;
	}
}
