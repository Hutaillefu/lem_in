/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pathfinding.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/30 15:33:23 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 15:33:24 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	get_all_moves(t_world *world, t_room *room)
{
	int val[2];

	val[0] = 0;
	val[1] = -1;
	get_all_moves_rec(world, room, -1, val);
}

int		get_all_utils(t_world *world, t_room *it, int path_index,
int *val[2])
{
	t_list *r;

	if (path_index != -1 && (world->paths[path_index] && (int)world->paths[path_index]->content_size == -1 && (*val)[0] != 0))
		return 0;
	(*val)[0]++;
	ft_lstpush(&(world->paths[path_index]), ft_lstnew(it, sizeof(it)));
	get_all_moves_rec(world, it, path_index, *val);
	if ((int)world->paths[path_index]->content_size != -1)
	{
		r = ft_lstpoplast(&(world->paths[path_index]));
		free(r);
	}
	(*val)[0]--;
	return (1);
}

void	get_all_moves_rec(t_world *w, t_room *room, int path_index,
int val[2])
{
	t_room	*it;
	int		i;

	if (!w || !room)
		return ;
	i = 0;
	while (++i < w->nb_rooms && (it = get_room_by_index(w, i)))
	{
		if (!is_link_exist(w->links[room->index][i]))
			continue;
		val[0] = val[0] < 0 ? 0 : val[0];
		if (val[0] == 0)
		{
			val[1] = i;
			path_index++;
			if (path_index >= w->nb_paths)
				return ;
		}
		if (i == 1)
		{
			ft_lstpush(&(w->paths[path_index]), ft_lstnew(it, sizeof(it)));
			w->paths[path_index]->content_size = -1;
			return ;
		}
		if (!get_all_utils(w, it, path_index, &val))
			return ;
	}
}

int		process_moves(t_world *w, t_list *r, int (*cpt)[2])
{
	t_room	*target;
	t_room	*current;

	if (!w)
		return (0);
	if (!r)
	{
		target = get_best_move(w);
		current = w->start_room;
	}
	else 
	{
		current = (t_room *)r->content;
		target = (t_room *)r->next->content;
	}
	if ((target->num_ant != 0 && target != w->end_room) ||
		!can_join(w, current, target))
		return (1);
	current->num_ant = 0;
	if (target == w->end_room)
	{
		(w->end_room->num_ant)++;
		set_ant_reach(w, (*cpt)[0]);
		(*cpt)[1] += (*cpt)[0] == (*cpt)[1] + 1 ? 1 : 0;
	}
	else
		target->num_ant = (*cpt)[0];
	set_link_free(&(w->links[current->index][target->index]), 0);
	add_move_print(&(w->print), (*cpt)[0], (char *)target->name);

	return (0);
}

void	pathfinding(t_world *world)
{
	t_list	*room;
	int		cpt[2];

	if (!world)
		return ;
	cpt[1] = 0;
	while (world->end_room->num_ant != world->nb_ants)
	{
		cpt[0] = cpt[1];
		while (++(cpt[0]) <= world->nb_ants)
		{
			if (is_ant_reach(world, cpt[0]))
				continue;
			room = get_room_where_ant(world, cpt[0]);
			if (process_moves(world, room, &cpt))
				continue;
		}
		add_print(&(world->print), "\n", 0);
		reinit_links(world);
	}
}
