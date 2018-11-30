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
#include <stdio.h>

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

/*
  ** Return the best move of 'moves'.
*/

t_move	*get_best_move(t_world *world, t_list *moves)
{
	t_list *it;
	t_move *best;
	// int		is_ant_best;
	// int		is_ant_it;
	(void)world;
	if (!moves)
		return (NULL);
	best = (t_move *)moves->content;
	it = moves->next;
	while (it)
	{
		if (((t_move *)it->content)->cost < best->cost)
		{
			//printf("Best move tools\n");
			best = (t_move *)it->content;
		}
		// else if (((t_move *)it->content)->cost == best->cost)
		// {
		// 	is_ant_best = get_room_by_index(world, best->target_index)->num_ant != 0;
		// 	is_ant_it = get_room_by_index(world, ((t_move *)it->content)->target_index)->num_ant != 0;
		// 	//printf("best ant :%d, it ant :%d\n", is_ant_best, is_ant_it);
		// 	if (is_ant_best && !is_ant_it)
		// 		best = (t_move *)it->content;
		// }
		it = it->next;
	} // PROBLEM DANS CETTE FCT, RENVOI LE MOVAI MOVE PArFOIS (OK POUR M1 MAIS PAS M7)
	return (best);
}

/*
  ** Desactivate all links from and to 'room'.
*/

void	avoid_path(t_world *world, t_room *room)
{
	int i;
	int index;

	if (!world || !room)
		return;
	i = 0;
	index = get_room_index(world, room->name);
	if (index == 1)
		return;
	while (i < world->nb_rooms)
	{
		set_link_exist(&(world->links[i][index]), 0);
		set_link_exist(&(world->links[index][i]), 0);
		i++;
	}
}
