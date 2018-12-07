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

void	get_all_moves(t_world *world, t_room *room, t_list **all_moves)
{
	int val[2];

	val[0] = 0;
	val[1] = -1;
	get_all_moves_rec(world, room, all_moves, val);
}

int		get_all_utils(t_world *world, t_room *it, t_list **all_moves,
int *val[2])
{
	(*val)[0] += (it->num_ant > 0 && (*val)[0] == 0) ? 1 : 0;
	if (!check_moves(all_moves, (*val)[1], (*val)[0] + 1))
	{
		(*val)[0]++;
		get_all_moves_rec(world, it, all_moves, *val);
		(*val)[0]--;
	}
	else
		return (0);
	(*val)[0] -= ((*val)[0] > 0 && it->num_ant > 0) ? 1 : 0;
	return (1);
}

void	get_all_moves_rec(t_world *w, t_room *room, t_list **all_moves,
int val[2])
{
	t_room	*it;
	int		ids[2];

	if (!w || !room)
		return ;
	ids[1] = 0;
	ids[0] = get_room_index(w, room->name);

	//printf("%s\n", room->name);

	while (++(ids[1]) < w->nb_rooms && (it = get_room_by_index(w, ids[1])))
	{
		if (!is_link_exist(w->links[ids[0]][ids[1]]))
			continue;
		val[0] = val[0] < 0 ? 0 : val[0];
		if (val[0] == 0)
			val[1] = ids[1];
		if (ids[1] == 1)
		{
			ft_lstadd(all_moves, create_move(val[0] + 1, val[1]));
			return ;
		}
		if (!get_all_utils(w, it, all_moves, &val))
			return ;
	}
}

int		process_moves(t_world *w, t_room *r, t_list *moves,
int (*cpt)[2])
{
	t_room	*target;
	t_move	*m;

	if (!moves || !(m = get_best_move(w, moves, r)))
		return (0);
	target = get_room_by_index(w, m->target_index);
	if ((target->num_ant != 0 && m->target_index != 1) ||
		!can_join(w, r, target))
	{
		free_list(&moves, free_move_maillon);
		return (1);
	}
	r->num_ant = 0;
	if (m->target_index == 1)
	{
		(w->end_room->num_ant)++;
		set_ant_reach(w, (*cpt)[0]);
		(*cpt)[1] += (*cpt)[0] == (*cpt)[1] + 1 ? 1 : 0;
	}
	else
		target->num_ant = (*cpt)[0];
	set_link_free(&(w->links[get_room_index(w, r->name)][m->target_index]), 0);
	add_move_print(&(w->print), (*cpt)[0], (char *)target->name);
	return (0);
}

void	pathfinding(t_world *world)
{
	t_list	*moves;
	t_room	*room;
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
			moves = NULL;
			get_all_moves(world, room, &moves);
			if (process_moves(world, room, moves, &cpt))
				continue;
			free_list(&moves, free_move_maillon);
		}
		add_print(&(world->print), "\n", 0);
		reinit_links(world);
	}
}
