/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 19:23:40 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/18 19:23:42 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

void display_transi(t_world *world)
{
	int i;
	int y;

	if (!world || !(world->links))
		return ;
	printf("\t");
	i = 0;
	while (i < world->nb_rooms)
	{
		printf("%s\t", get_room_by_index(world, i)->name);
		i++;
	}
	printf("\n");

	i = 0;
	while (i < world->nb_rooms)
	{
		y = 0;
		printf("%s\t", get_room_by_index(world, i)->name);
		while (y < world->nb_rooms)
		{
			if (is_link_exist(world->links[y][i]))
			{
				if (is_link_free(world->links[y][i]))
					printf("1\t");
				else
					printf("2\t");
			}
			else
				printf("0\t");
			y++;
		}
		printf("\n");
		i++;
	}
}	

const char *room_name(t_list *maillon)
{
	t_room	*room;

	if (!maillon || !(maillon->content))
		return (NULL);
	if (!(room = (t_room *)maillon->content))
		return (NULL);
	return room->name;	
}

int	get_room_index_in_list(t_list *rooms, const char *name)
{
	t_list *it;
	int	i;

	if (!rooms || !name)
		return (-1);
	it = rooms;
	i = 0;
	while (it)
	{
		if (room_name(it) && ft_strcmp(name, room_name(it)) == 0)
			return (i);
		it = it->next;
		i++;
	}
	return (-1);
}

/*
  ** Return 0 for start_room, 1 for end_room and index in world's list rooms for others.
*/
int	get_room_index(t_world *world, const char *name)
{
	if (!world || !name)
		return (-1);
	if (world->start_room && world->start_room->name && ft_strcmp(name, world->start_room->name) == 0)
		return (0);
	else if (world->end_room && world->end_room->name && ft_strcmp(name, world->end_room->name) == 0)
		return (1);
	return (get_room_index_in_list(world->rooms, name) + 2);
}

t_room	*get_room_by_index(t_world *world, int index)
{
	if (!world || index < 0)
		return (NULL);
	if (index == 0)
		return (world->start_room);
	else if (index == 1)
		return (world->end_room);
	return ((t_room *)(ft_lstgetindex(&(world->rooms), index - 2)->content));
}

int	is_room_name_exist(t_world *world, const char *name)
{
	if (!world || !name)
		return (0);
	return (get_room_index(world, name) >= 0);
	
}

/*
  ** Parse a room from line and add it to the world's room list.
*/

int	process_room(const char *line, t_world *world)
{
	t_room	*room;
	
	if (!line || !world)
		return (0);
	if (!(room = parse_room(line)))
		return (0);
	if (!(add_room(world, room)))
	{
		free_room(&room);
		return (0);
	}
	return (1);
}

int	add_link(t_world *world, int start_index, int end_index)
{
	if (!world || !world->links || start_index < 0 || end_index < 0)
		return (0);
	set_link_exist(&(world->links[start_index][end_index]), 1);
	set_link_free(&(world->links[start_index][end_index]), 1);
	return (1);
}

void	exit_lemin(t_world **world, int is_error)
{
	if (!world || !(*world))
		return ;
	free_world(world);
	if (is_error)
		ft_putstr_fd("Error\n", 2);
	exit(0);
}

int		can_run(t_world *world)
{
	t_list	*moves;

	if (!world || !(world->start_room) || !(world->end_room) || !(world->links))
		return (0);
	moves = NULL;
	get_all_moves_rec(world, world->start_room, &moves, 0, -1);
	if (!moves)
		return (0);
	free_list(&moves, free_move_maillon);
	return (1);
}

int		main(int argc, char **argv)
{
	t_world	*world;

	(void)argc;
	(void)argv;

	if (!(world = create_world()))
		return (0);
	
	if (!parse_num_ants(world))
		exit_lemin(&world, 1);
	printf("Nb ants : %d\n", world->nb_ants);

	parse_map(world);
	
	if (!can_run(world))
		exit_lemin(&world, 1);
	
	init_ants(world);

	//display_transi(world);

	pathfinding(world);

	exit_lemin(&world, 0);

	return (0);
}
