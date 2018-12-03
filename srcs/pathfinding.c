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
#include <stdio.h>

void	display_room(t_room *room)
{
	if (!room)
		return ;
	printf("room name:%s, x:%d, y:%d, num_ant:%d\n", room->name, room->x, room->y, room->num_ant);
}

t_list	*create_move(int cost, int target_index)
{
	t_move *move;

	move = (t_move *)malloc(sizeof(t_move));
	move->cost = cost;
	move->target_index = target_index;
	return (ft_lstnew(move, sizeof(move)));
}

int		check_moves(t_list **all_moves, int target_index, int cost)
{
	t_list *it;

	if (!all_moves)
		return (0);
	it = *all_moves;
	while (it)
	{
		if (((t_move *)(it)->content)->target_index == target_index &&
		cost >= ((t_move *)(it)->content)->cost)
			return (1);
		it = it->next;
	}
	return (0);
}

void	reset_num_ant(t_world *world)
{
	int i;

	if (!world)
		return ;
	i = 0;
	while (i < world->nb_rooms)
	{
		get_room_by_index(world, i)->num_ant = 0;
		i++;
	}
}

t_room	*pop_room(t_list **lst)
{
	t_room	*room;
	t_list	*maillon;

	if (!lst)
		return (NULL);
	if (!(maillon = ft_lstpop(lst)))
		return (NULL);
	room = (t_room *)maillon->content;
	free(maillon);
	return (room);
}

void	bfs_2(t_world *world, t_list **rooms, t_room *room, int *nb_paths)
{
	t_room	*target;
	int		val[3];

	val[0] = 0;
	val[1] = 0;
	val[2] = get_room_index(world, room->name);
	while (++(val[0]) < world->nb_rooms)
	{
		target = get_room_by_index(world, val[0]);
		if (!(is_joinable(world, room, target) && target->num_ant != 1))
			continue ;
		set_link_exist(&(world->links[val[2]][val[0]]), 1);
		set_link_exist(&(world->links[val[0]][val[2]]), 0);
		(val[1])++;
		if (val[0] != 1)
			target->num_ant = 1;
		else
		{
			(*nb_paths)++;
			break ;
		}
		ft_lstadd(rooms, ft_lstnew(target, sizeof(target)));
	}
	if (val[1] == 0)
		avoid_path(world, val[2]);
}

int		bfs(t_world *world, t_room *start)
{
	t_list	*rooms;
	int		nb_paths;

	if (!world)
		return (0);
	rooms = NULL;
	nb_paths = 0;
	world->start_room->num_ant = 1;
	ft_lstpush(&rooms, ft_lstnew(start, sizeof(start)));
	while (ft_lstlen(&rooms) > 0)
		bfs_2(world, &rooms, pop_room(&rooms), &nb_paths);
	reset_num_ant(world);
	//printf("%d paths detected\n", nb_paths);
	return (nb_paths);
}

void	get_all_moves_rec(t_world *world, t_room *room, t_list **all_moves, int cost, int target_index)
{
	int		index;
	t_room	*it;
	int		room_index;

	if (!world || !room)
		return ;
	index = 0;
	room_index = get_room_index(world, room->name);
	while (++index < world->nb_rooms && (it = get_room_by_index(world, index)))
	{
		if (!is_link_exist(world->links[room_index][index]))
			continue;
		target_index = cost == 0 ? index : target_index;
		if (index == 1)
		{
			ft_lstadd(all_moves, create_move(cost + 1, target_index));
			return ;
		}
		else
		{
			cost += (it->num_ant > 0 && cost == 0) ? 1 : 0;
			set_link_exist(&(world->links[room_index][index]), 0);
			if (!check_moves(all_moves, target_index, cost + 1))
				get_all_moves_rec(world, it, all_moves, cost + 1, target_index);
			else
				return ;
			set_link_exist(&(world->links[room_index][index]), 1);
			cost -= (cost > 0 && it->num_ant > 0) ? 1 : 0;
		}
	}
}

void	pathfinding(t_world *world)
{
	t_list	*moves;
	t_room	*room;
	t_move	*move;
	int		i;
	int		start;
	t_room *target;

	if (!world)
		return ;
	start = 1;
	while (world->end_room->num_ant != world->nb_ants)
	{
		i = start;
		while (i <= world->nb_ants)
		{
			if (is_ant_reach(world, i))
			{
				i++;
				continue;
			}
			room = get_room_where_ant(world, i);
			moves = NULL;
			get_all_moves_rec(world, room, &moves, 0, -1);
			if (moves)
			{
				move = get_best_move(world, moves);
				target = get_room_by_index(world, move->target_index);
				if ((target->num_ant != 0 && move->target_index != 1) ||
					!can_join(world, room, target))
				{
					free_list(&moves, free_move_maillon);
					i++;
					continue;
				}
				room->num_ant = 0;
				if (move->target_index == 1)
				{
					(world->end_room->num_ant)++;
					set_ant_reach(world, i);
					if (i == start + 1)
						start++;
				}
				else
					target->num_ant = i;
				set_link_free(&(world->links[get_room_index(world, room->name)][move->target_index]), 0);
				set_link_free(&(world->links[move->target_index][get_room_index(world, room->name)]), 0);
				add_move_print(&(world->print), i, (char *)target->name);
				free_list(&moves, free_move_maillon);
			}
			i++;
		}
		add_print(&(world->print), "\n", 0);
		reinit_links(world);
	}
}
