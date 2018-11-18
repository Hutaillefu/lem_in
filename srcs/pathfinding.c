#include "lem_in.h"
#include <stdio.h>

void	display_room(t_room *room)
{
	if (!room)
		return;
	printf("room name:%s, x:%d, y:%d, num_ant:%d\n", room->name, room->x, room->y, room->num_ant);
}

int	is_joinable(t_world *world, t_room *from, t_room *to)
{
	int from_index;
	int to_index;

	if (!world || !(world->links) || !from || !to)
		return (0);
	
	from_index = get_room_index(world, from->name);
	to_index = get_room_index(world, to->name);

	if (from_index < 0 || to_index < 0)
		return (0);
	
	return (is_link_exist(world->links[from_index][to_index])); // check if link already used  // && to->num_ant == 0);
}

int	can_join(t_world *world, t_room *from, t_room *to)
{
	int from_index;
	int to_index;

	if (!world || !(world->links) || !from || !to)
		return (0);
	
	from_index = get_room_index(world, from->name);
	to_index = get_room_index(world, to->name);

	if (from_index <0 || to_index < 0)
		return (0);
	
	return (is_link_free(world->links[from_index][to_index]));
}

void	get_all_moves_rec(t_world *world, t_room *room, t_list *all_moves, int cost, int target_index)
{
	int	index;
	t_room	*it;
	t_move	*move;
	
	index = 1;
	while (index < world->nb_rooms)
	{
		it = get_room_by_index(world, index);
		if (ft_strcmp(it->name, room->name) != 0 && is_joinable(world, room, it) &&
		    can_join(world, room, it))
		{
			if (cost == 0)
				target_index = index;
			if (index == 1) // end_room
			{
				move = (t_move *)malloc(sizeof(t_move));
				move->cost = cost + 1;
				move->target_index = target_index;
				ft_lstadd(&all_moves, ft_lstnew(move, sizeof(move)));
				printf("Path of cost %d added with target index %d\n", move->cost, move->target_index);
			}
			else
			{
				if (it->num_ant > 0) // ant on target cell need up cost
					cost++;
				get_all_moves_rec(world, it, all_moves, cost + 1, target_index);
			}
		}
		index++;
	}
}

t_list	*get_all_move(t_world *world, t_room *room)
{
	t_list	*moves;

	if (!world || !(world->links) || !room)
		return (NULL);
	moves = NULL;

	return (moves);
}

int	best_move(t_world *world, t_room *room)
{
	int	curr_index;
	int	best;
	int 	tmp;
	int	index;

	if (!world || !(world->links) || !room)
	{
		printf("Null ref error\n");
		return (0);
	}
	if ((index = get_room_index(world, room->name)) < 0)
	{
		printf("Bad index error\n");
		return (0);
	}	
	curr_index = 1; // do not take start as target
	best = 0;
	while (curr_index < world->nb_rooms)
	{
		tmp = 0;
		if (ft_strcmp(get_room_by_index(world, curr_index)->name, room->name) != 0 &&
		    is_joinable(world, room, get_room_by_index(world, curr_index)))
		{
			printf("%s -> %s\n", room->name, get_room_by_index(world, curr_index)->name);
			tmp = 1 + best_move(world, get_room_by_index(world, curr_index));
			printf("Best update from %d to %d\n", best, tmp);
		}
		if ((best == 0 && tmp > 0) || (tmp < best && tmp > 0))
		{
			printf("new best : %d\n", tmp);
			best = tmp;
		}
		curr_index++;
	}
	return (best);
}
