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
	if (!world || !(world->links) || !from || !to)
		return (0);
	if (from->index < 0 || to->index < 0)
		return (0);
	return (is_link_exist(world->links[from->index][to->index]) ||
	is_link_exist(world->links[to->index][from->index]));
}

/*
  ** Return true if 'from'->'to' or 'to'->'from' is free.
*/

int		can_join(t_world *world, t_room *from, t_room *to)
{
	if (!world || !(world->links) || !from || !to)
		return (0);
	if (from->index < 0 || to->index < 0)
		return (0);
	return (is_link_free(world->links[from->index][to->index]) ||
	is_link_free(world->links[to->index][from->index]));
}

void	get_best_utils(t_world *world, t_room *room, t_move **best, t_list *it)
{
	int		is_ant_best;
	int		is_ant_it;

	if (!is_joinable(world, room, get_room_by_index(world,
	((t_move *)it->content)->target_index)))
		return ;
	if (!(*best) || ((t_move *)it->content)->cost < (*best)->cost)
		*best = (t_move *)it->content;
	else if (((t_move *)it->content)->cost == (*best)->cost)
	{
		is_ant_best = get_room_by_index(world,
		(*best)->target_index)->num_ant != 0;
		is_ant_it = get_room_by_index(world,
		((t_move *)it->content)->target_index)->num_ant != 0;
		if (is_ant_best && !is_ant_it)
			*best = (t_move *)it->content;
	}
}

/*
  ** Return the best move of 'moves'.
*/

t_room	*get_best_move(t_world *w)
{
	int		i;
	t_room	*best;
	int		cost;
	int		tmp;

	if (!w)
		return (NULL);
	i = 0;
	while (!w->paths[i])
		i++;
	best = (t_room *)w->paths[i]->content;
	cost = ft_lstlen(&(w->paths[i])) + (best->num_ant > 0 ? 1 : 0);
	while (++i < w->nb_paths)
	{
		if (!w->paths[i])
			continue;
		tmp = ((t_room *)w->paths[i]->content)->num_ant > 0 ? 1 : 0;
		if (can_join(w, w->start_room, (t_room *)w->paths[i]->content)
		&& ft_lstlen(&(w->paths[i])) + tmp <= cost)
		{
			cost = ft_lstlen(&(w->paths[i])) + tmp;
			best = (t_room *)w->paths[i]->content;
		}
	}
	return (best);
}

/*
  ** Desactivate all links from and to 'room'.
*/

void	avoid_path(t_world *world, int room_index)
{
	int i;

	if (!world || room_index == 1)
		return ;
	i = 0;
	while (i < world->nb_rooms)
	{
		set_link_exist(&(world->links[i][room_index]), 0);
		set_link_exist(&(world->links[room_index][i]), 0);
		i++;
	}
}
