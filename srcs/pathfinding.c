#include "lem_in.h"
#include <stdio.h>

void display_room(t_room *room)
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

int nb_voisins(t_world *world, t_room *room)
{
	int i;
	t_room *voisin;
	int res;

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

int check_moves(t_list **all_moves, int target_index, int cost)
{
	t_list *it;

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

void avoid_path(t_world *world, t_room *room)
{
	int i;
	int index;

	if (!world || !room)
		return;
	i = 0;
	index = get_room_index(world, room->name);
	if (index == 1)
		return;
	//printf("avoiding path to %s\n", room->name);
	while (i < world->nb_rooms)
	{
		set_link_exist(&(world->links[i][index]), 0);
		set_link_exist(&(world->links[index][i]), 0);
		i++;
	}
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

int bfs(t_world *world, t_room *start, int nb_paths)
{
	t_list *rooms;
	t_room *room;
	t_room *target;
	int i;
	int y;
	int paths = nb_paths;

	if (!world)
		return 0;
	rooms = NULL;
	world->start_room->num_ant = 1;
	ft_lstpush(&rooms, ft_lstnew(start, sizeof(start)));
	while (ft_lstlen(&rooms) > 0)
	{
		room = (t_room *)(ft_lstpop(&rooms)->content);
		i = 0;
		y = 0;
		while (i < world->nb_rooms)
		{
			target = get_room_by_index(world, i);
			if (is_joinable(world, room, target) && target->num_ant != 1)
			{
				//set_link_exist(&(world->links[i][get_room_index(world, room->name)]), 0); //here
				y++;
				if (i != 1)
					target->num_ant = 1;
				else
				{
					nb_paths--;
				}
				if (nb_paths == 0)
				{
					reset_num_ant(world);
					printf("%d paths detected\n", paths);
					return paths;
				}
				ft_lstadd(&rooms, ft_lstnew(target, sizeof(target)));
			}
			i++;
		}
		if (y == 0)
			avoid_path(world, room);
	}
	return (0);
}

int get_all_moves_rec(t_world *world, t_room *room, t_list **all_moves, int cost, int target_index)
{
	int index;
	t_room *it;

	if (!world || !room)
		return (0);
		
	index = 1;
	while (index < world->nb_rooms)
	{
		it = get_room_by_index(world, index);
		if (!is_joinable(world, room, it))
		{
			index++;
			continue;
		}

		//printf("%s -> %s\n", room->name, it->name);
		// if (get_room_index(world, room->name) == 25)
		// 	sleep(10);

		if (cost == 0)
			target_index = index;

		if (index == 1)
		{
			//set_link_exist(&(world->links[index][get_room_index(world, room->name)]), 0);
			ft_lstadd(all_moves, create_move(cost + 1, target_index));
			//printf("Path of cost %d added with target index %d\n", cost + 1, target_index);
			return (1);
		}
		else
		{
			if (it->num_ant > 0 && cost == 0) // ant on target cell need up cost
				cost++;
			set_link_exist(&(world->links[index][get_room_index(world, room->name)]), 0);
			set_link_exist(&(world->links[get_room_index(world, room->name)][index]), 0);

			if (!check_moves(all_moves, target_index, cost + 1))
				get_all_moves_rec(world, it, all_moves, cost + 1, target_index);
			else
			{
				set_link_exist(&(world->links[get_room_index(world, room->name)][index]), 1);
				return (0);
			}
			set_link_exist(&(world->links[get_room_index(world, room->name)][index]), 1);

			if (cost > 0 && it->num_ant > 0)
				cost--;
		}
		index++;
	}
	return (0);
}

int is_ant_reach(t_world *world, int ant_num)
{
	int int_index; // index in world->ants
	int index;	 // index of bit in int of 32 bits

	if (!world)
		return (0);
	ant_num--;
	int_index = ant_num / 32;
	index = ant_num % 32;
	return ((world->ants[int_index] >> (31 - index)) & 1);
}

void set_ant_reach(t_world *world, int ant_num)
{
	int int_index; // index in world->ants
	int index;	 // index of bit in int of 32 bits

	if (!world)
		return;
	ant_num--;
	int_index = ant_num / 32;
	index = ant_num % 32;
	world->ants[int_index] |= (1 << (31 - index));
}



// Calculate each path from each start voisin.
// Keep the nb best where nb is U KNOW


void pathfinding(t_world *world)
{
	t_list *moves;
	t_room *room;
	t_move *move;
	int i;
	int start;

	if (!world)
		return;

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

				if (get_room_by_index(world, move->target_index)->num_ant != 0 && move->target_index != 1)
				{
					free_list(&moves, free_move_maillon);
					i++;
					continue;
				}

				if (!can_join(world, room, get_room_by_index(world, move->target_index)))
				{
					free_list(&moves, free_move_maillon);
					i++;
					continue;
				}

			//	printf(" | Get %d moves from %s ", ft_lstlen(&moves), room->name);

				room->num_ant = 0;

				if (move->target_index == 1)
				{
					(world->end_room->num_ant)++;
					set_ant_reach(world, i);
					if (i == start + 1)
						start++;
					set_link_free(&(world->links[get_room_index(world, room->name)][move->target_index]), 0);
					set_link_free(&(world->links[move->target_index][get_room_index(world, room->name)]), 0);
					printf("L%d-%s ", i, get_room_by_index(world, move->target_index)->name);
					add_move_print(&(world->print), i, (char *)get_room_by_index(world, move->target_index)->name);
				}
				else
				{
					get_room_by_index(world, move->target_index)->num_ant = i;
					set_link_free(&(world->links[get_room_index(world, room->name)][move->target_index]), 0);
					set_link_free(&(world->links[move->target_index][get_room_index(world, room->name)]), 0);
					printf("L%d-%s ", i, get_room_by_index(world, move->target_index)->name);
					add_move_print(&(world->print), i, (char *)get_room_by_index(world, move->target_index)->name);
				}
				free_list(&moves, free_move_maillon);
			}
			else
			{
				printf("No path from %s\n", room->name);
			}
			i++;
		}
		//add_print(&(world->print), "\n", 0);
		printf("\n");
		reinit_links(world);
	}
}
