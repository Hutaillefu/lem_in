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

void	add_index(t_list **indexes, int index)
{
	int	*value;

	if (!indexes)
		return ;
	value = (int *)malloc(sizeof(int));
	*value = index;
	ft_lstadd(indexes, ft_lstnew(value, sizeof(value)));
}

void	rm_index(t_list **indexes, int index)
{
	t_list	*it;
	t_list	*prev;

	if (!indexes)
		return ;
	if (*(int *)(*indexes)->content == index)
	{
		it = *indexes;
		*indexes = it->next;
		free(it->content);
		free(it);
		return ;
	}
	prev = *indexes;
	it = prev->next;
	while (it)
	{
		if (*(int *)it->content == index)
		{
			prev->next = it->next;
			free(it->content);
			free(it);
			return ;
		}
		prev = it;
		it = it->next;
	}
}

int indexes_contains(t_list **indexes, int index)
{
	t_list *it;
	if (!indexes)
		return (0);
	it = *indexes;
	while (it)
	{
		if ((*(int *)it->content) == index)
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
		if ((cost == 0 && !can_join(world, room, it)) || // cant join first voisins
			ft_strcmp(it->name, room->name) == 0 ||		 // can't join same room
			!is_joinable(world, room, it))				 // link do not exist
		{
			index++;
			continue;
		}
		if (indexes_contains(indexes, index))
		{
			index++;
			continue;
		}

		if (cost == 0)
			target_index = index;

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
			get_all_moves_rec(world, it, all_moves, cost + 1, target_index, indexes);
			rm_index(indexes, index);
			// cost-- ?
		}
		index++;
	}
}

/*
  ** Set each existing links as free.
*/

void reinit_links(t_world *world)
{
	int i;
	int y;

	i = 0;
	while (i < world->nb_rooms)
	{
		y = 0;
		while (y < world->nb_rooms)
		{
			if (is_link_exist(world->links[i][y]))
				set_link_free(&(world->links[i][y]), 1);
			else if (is_link_exist(world->links[y][i]))
				set_link_free(&(world->links[y][i]), 1);
			y++;
		}
		i++;
	}
}

/*
  ** Return the best move of 'moves'
*/

t_move *get_best_move(t_list *moves)
{
	t_list *it;
	t_move *best;

	if (!moves)
		return (NULL);
	best = (t_move *)moves->content;
	it = moves->next;
	while (it)
	{
		if (((t_move *)it->content)->cost < best->cost)
			best = (t_move *)it->content;
		it = it->next;
	}
	return best;
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
			moves = NULL;
			indexes = NULL;
			get_all_moves_rec(world, room, &moves, 0, -1, &indexes);
			free_list(&indexes, free_index_maillon);
			if (moves)
			{
				room->num_ant = 0;
				move = get_best_move(moves);
				//printf("selected move, cost=%d, target_index=%d\n", move->cost, move->target_index);

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
