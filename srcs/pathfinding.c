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

	if (is_link_exist(world->links[from_index][to_index]) && ft_strcmp(to->name, world->end_room->name) == 0)
		return (1);

	return (is_link_exist(world->links[from_index][to_index]) && to->num_ant == 0); // check if link already used  // && to->num_ant == 0);
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

t_list	*create_move(int cost, int target_index)
{
	t_move	*move = (t_move *)malloc(sizeof(t_move));
	move->cost = cost;
	move->target_index = target_index;
	return (ft_lstnew(move, sizeof(move)));
}

void	get_all_moves_rec(t_world *world, t_room *room, t_list **all_moves, int cost, int target_index)
{
	int	index;
	t_room	*it;


	if (!world || !room)
	{
		printf("NULL\n");
		return ;
	}
	index = 1;
	while (index < world->nb_rooms)
	{
		it = get_room_by_index(world, index);

		if (ft_strcmp(it->name, room->name) != 0 && is_joinable(world, room, it) &&
		    can_join(world, room, it))
		{
			//printf("%s can go to %s\n", room->name, it->name);
			if (cost == 0)
				target_index = index;
			if (index == 1) // end_room
			{
				ft_lstadd(all_moves, create_move(cost + 1, target_index));
				//printf("Path of cost %d added with target index %d\n", cost + 1, target_index);
			}
			else
			{
				if (it->num_ant > 0) // ant on target cell need up cost
					cost++;
				get_all_moves_rec(world, it, all_moves, cost + 1, target_index);
				// cost-- ?
			}
		}
		index++;
	}
}

t_room	*get_room_where_ant(t_world * world, t_ant *ant)
{
	int 	i;
	t_room	*room;

	if (!world || !ant)
		return (NULL);
	i = 2;
	room = NULL;
	while (i < world->nb_rooms)
	{
		room = get_room_by_index(world, i);
		if (room->num_ant == ant->num)
			return (room);
		i++;
	}
	
	return world->start_room;
}

void	reinit_links(t_world *world)
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
			y++;
		}
		i++;
	}
}

void	pathfinding(t_world *world)
{
	t_list	*moves;
	t_room	*room;
	t_move	*move;
	t_list	*it;
	t_ant	*ant;

	if (!world)
		return ;

	while (world->end_room->num_ant != world->nb_ants)
	{
		it = world->ants;
		while (it)
		{
			ant = (t_ant *)it->content;
			if (ant->is_reach)
			{
				//printf("ant %d already reached\n", ant->num);
				it = it->next;
				continue;
			}
			room = get_room_where_ant(world, ant);
			moves = NULL;
			get_all_moves_rec(world, room, &moves, 0, -1);
			if (moves)
			{
				room->num_ant = 0;
				move = (t_move *)moves->content;
				//printf("selected move, cost=%d, target_index=%d\n", move->cost, move->target_index);

				if (move->target_index == 1)
				{
					world->end_room->num_ant++;
					ant->is_reach = 1;
					set_link_free(&(world->links[get_room_index(world, room->name)][move->target_index]), 0);
					printf("L%d-%s ", ant->num, get_room_by_index(world, move->target_index)->name);
				}
				else
				{
					get_room_by_index(world, move->target_index)->num_ant = ant->num;
					set_link_free(&(world->links[get_room_index(world, room->name)][move->target_index]), 0);
					printf("L%d-%s ", ant->num, get_room_by_index(world, move->target_index)->name);
				}
			}
			//else
			//	printf("no path\n");
			it = it->next;
		}
		printf("\n");
		reinit_links(world);
	}
}	
