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
