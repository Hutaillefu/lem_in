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

void get_all_moves_rec(t_world *world, t_room *room, t_list **all_moves, int cost, int target_index, t_list **indexes)
{
	int index;
	t_room *it;

	if (!world || !room)
		return;
	index = 1;
	//display_room(room);
	while (index < world->nb_rooms)
	{
		it = get_room_by_index(world, index);
		if (ft_strcmp(it->name, room->name) == 0 ||	// can't join same room
			!is_joinable(world, room, it))			// link does not exist												
		{
			//printf("Cant %s -> %s\n", room->name, it->name);
			//printf("is_joinable %d\n", is_joinable(world, room, it));
			index++;
			continue;
		}

		if (indexes_contains(indexes, index))
		{
			index++;
			continue;
		}

		//printf("%s -> %s\n", room->name, it->name);

		if (cost == 0)
			target_index = index;

		if (cost == 0 && (can_join(world, room, it) && it->num_ant != 0)) // Ant on first voisin
			cost++;
			
		if (index == 1) 
		{
			ft_lstadd(all_moves, create_move(cost + 1, target_index));
			//printf("Path of cost %d added with target index %d\n", cost + 1, target_index);
		}
		else
		{
			if (it->num_ant > 0) // ant on target cell need up cost
				cost++;
			add_index(indexes, index);
			//printf("%s->%s\n", room->name, it->name);
			get_all_moves_rec(world, it, all_moves, cost + 1, target_index, indexes);
			rm_index(indexes, index);
			//cost--;
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
			free_list(&indexes, free_index_maillon);
			if (moves)
			{
				//printf("Get best for move %s\n", room->name);
				move = get_best_move(world, moves);
				//printf("selected move, cost=%d, target_index=%d\n", move->cost, move->target_index);

				if (get_room_by_index(world, move->target_index)->num_ant != 0 && move->target_index != 1)
				{
					//printf("room %s is already used\n", get_room_by_index(world, move->target_index)->name);
					free_list(&moves, free_move_maillon);
					it = it->next;
					continue;
				}

				if (!can_join(world, room, get_room_by_index(world, move->target_index)))
				{
					free_list(&moves, free_move_maillon);
					it = it->next;
					continue;
				}

				room->num_ant = 0;

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
					get_room_by_index(world, move->target_index)->num_ant = ant->num;
					set_link_free(&(world->links[get_room_index(world, room->name)][move->target_index]), 0);
					set_link_free(&(world->links[move->target_index][get_room_index(world, room->name)]), 0);
					printf("L%d-%s ", ant->num, get_room_by_index(world, move->target_index)->name);
				}
				free_list(&moves, free_move_maillon);
			}
			it = it->next;
		}
		printf("\n");
		reinit_links(world);
	}
}
