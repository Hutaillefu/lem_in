#include "lem_in.h"
#include <stdio.h>

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
	
	return (world->links[from_index][to_index]);
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
		//	if (curr_index == 1 && tmp < best)
		//	{
			//	best = tmp;
				printf("new best : %d\n", tmp);
		//	}
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
