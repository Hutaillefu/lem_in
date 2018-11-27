#include "lem_in.h"
#include <stdio.h>

void	display_room(t_room *room)
{
	if (!room)
		return;
	printf("room name:%s, x:%d, y:%d, num_ant:%d\n", room->name, room->x, room->y, room->num_ant);
}

t_list *create_move(int cost, int target_index)
{
	t_move *move = (t_move *)malloc(sizeof(t_move));
	move->cost = cost;
	move->target_index = target_index;
	return (ft_lstnew(move, sizeof(move)));
}

int		nb_voisins(t_world *world, t_room *room)
{
	int		i;
	t_room	*voisin;
	int		res;

	if (!world || !room)
		return (0);
	i = 0;
	res = 0;
	while (i < world->nb_rooms)
	{
		voisin = get_room_by_index(world, i);
		if (is_joinable(world, room, voisin))
			res++;
		i++;
	}
	return (res);
}

void	parcours(t_world *world, t_room *room, t_list **indexes)
{
	int	i;
	t_room	*target;

	printf("%s -> ", room->name);

	i = 1;
	while (i < world->nb_rooms)
	{
		target = get_room_by_index(world, i);
		if (!indexes_contains(indexes, i) && is_joinable(world, room, target))
		{
			if (i == 1)
			{
				printf("END\n");
				return ;
			}
			//printf("%s\n", target->name);
			add_index(indexes, i);
			parcours(world, target, indexes);
		}
		i++;
	}
}

int		check_moves(t_list **all_moves, int target_index, int cost)
{
	t_list	*it;

	if (!all_moves)
		return (0);
	it = *all_moves;
	while (it)
	{
		if (((t_move *)(it)->content)->target_index == target_index && cost >= ((t_move *)(it)->content)->cost)
			return (1);
		it = it->next;
	}
	return (0);
}

void get_all_moves_rec(t_world *world, t_room *room, t_list **all_moves, int cost, int target_index, t_list **indexes)
{
	int index;
	t_room *it;

	if (!world || !room)
		return;
	index = 1;
	while (index < world->nb_rooms)
	{
		it = get_room_by_index(world, index);
		if (!is_joinable(world, room, it))											
		{
			index++;
			continue;
		}

		if (cost == 0)
			target_index = index;

		if (index == 1) 
		{
			ft_lstadd(all_moves, create_move(cost + 1, target_index));
			printf("Path of cost %d added with target index %d\n", cost + 1, target_index);
			return ;
		}
		else
		{
			if (it->num_ant > 0) // ant on target cell need up cost
				cost++;

			set_link_exist(&(world->links[index][get_room_index(world, room->name)]), 0);
			set_link_exist(&(world->links[get_room_index(world, room->name)][index]), 0);

			if (!check_moves(all_moves, target_index, cost + 1))
				get_all_moves_rec(world, it, all_moves, cost + 1, target_index, indexes);
			else
			{
				set_link_exist(&(world->links[get_room_index(world, room->name)][index]), 1);
				return ;
			}
			set_link_exist(&(world->links[get_room_index(world, room->name)][index]), 1);

			if (cost > 0 && it->num_ant > 0)
				cost--;
		}
		index++;
	}
}

void pathfinding(t_world *world)
{
	t_list *moves;
	t_room *room;
	t_move *move;
	t_list *it;
	t_ant *ant;
	t_list *indexes;

	if (!world)
		return;

	while (world->end_room->num_ant != world->nb_ants)
	{
		it = world->ants;
		while (it)
		{
			ant = (t_ant *)it->content;
			if (ant->is_reach)
			{
				it = it->next;
				continue;
			}
			room = get_room_where_ant(world, ant);
			//display_room(room);
			moves = NULL;
			indexes = NULL;
			get_all_moves_rec(world, room, &moves, 0, -1, &indexes);
			//free_list(&indexes, free_index_maillon);
			if (moves)
			{
				move = get_best_move(world, moves);
				//printf("Get %d moves from %s\n", ft_lstlen(&moves), room->name);
				//printf("%s -> %s, cost=%d\n", room->name, get_room_by_index(world, move->target_index)->name, move->cost);

				if (get_room_by_index(world, move->target_index)->num_ant != 0 && move->target_index != 1)
				{
					//printf("room %s is already used with ant num %d\n", get_room_by_index(world, move->target_index)->name, get_room_by_index(world, move->target_index)->num_ant);
					free_list(&moves, free_move_maillon);
					it = it->next;
					continue;
				}

				if (!can_join(world, room, get_room_by_index(world, move->target_index)))
				{
					//printf("Cant join target\n");
					free_list(&moves, free_move_maillon);
					it = it->next;
					continue;
				}

				room->num_ant = 0;

				//printf("%s -> %s\n", room->name, get_room_by_index(world, move->target_index)->name);

				if (move->target_index == 1)
				{
					world->end_room->num_ant++;
					ant->is_reach = 1;
					set_link_free(&(world->links[get_room_index(world, room->name)][move->target_index]), 0);
					set_link_free(&(world->links[move->target_index][get_room_index(world, room->name)]), 0);
					printf("L%d-%s ", ant->num, get_room_by_index(world, move->target_index)->name);
				}
				else
				{
					//printf("ant num %d in room %s\n", ant->num, get_room_by_index(world, move->target_index)->name);
					get_room_by_index(world, move->target_index)->num_ant = ant->num;
					set_link_free(&(world->links[get_room_index(world, room->name)][move->target_index]), 0);
					set_link_free(&(world->links[move->target_index][get_room_index(world, room->name)]), 0);
					printf("L%d-%s ", ant->num, get_room_by_index(world, move->target_index)->name);
				}
				free_list(&moves, free_move_maillon);
			}
			else
				printf("No path\n");
			it = it->next;
		}
		printf("\n");
		reinit_links(world);
	}
}
